package com.montevideo.cisco.tutorial;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

//import io.vertx.rxjava.core.eventbus.EventBus;

import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import io.netty.handler.timeout.TimeoutException;
import io.vertx.core.file.OpenOptions;
import io.vertx.rxjava.core.AbstractVerticle;
import io.vertx.rxjava.core.RxHelper;
import io.vertx.rxjava.core.Vertx;
import io.vertx.rxjava.core.eventbus.EventBus;
import io.vertx.rxjava.core.file.AsyncFile;
import io.vertx.rxjava.core.file.FileSystem;
import io.vertx.rxjava.core.http.HttpServer;
import rx.Observable;
import rx.Scheduler;
import rx.Subscriber;

import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.QueueingConsumer;

/**
 * Hello world!
 *
 */
public class App extends AbstractVerticle {

	// input = App3.class.getClassLoader().getResourceAsStream(filename);
	// prop.load(getClass().getClassLoader().getResourceAsStream("config.properties"));
	private static int port = 9090;
	private static final String DCNMEXCHANGENAME = "DCNMExchange";
	private static final String DCNMHOST = "172.27.252.70";
	static int numMessages = 0; 
	
	private static final String ADDRESS = "ping-address";
	 
	private static String blockingLoad(String id) {

		    // Simulate a blocking action
		    try {
		      Thread.sleep(100);
		      return "someData for " + id;
		    } catch (InterruptedException e) {
		      e.printStackTrace();
		      return null;
		    }
		  }
	 
	 
	public static void main(String[] args) throws InterruptedException,
			IOException, TimeoutException {
		
		
		
		try {
			testDCNM();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		/*    Vertx vertx = Vertx.vertx();
		   
		
		    Observable<String> o = Observable.just("someID1", "someID2", "someID3", "someID4");

		    // This scheduler can execute blocking actions
		    Scheduler scheduler = io.vertx.rxjava.core.RxHelper.blockingScheduler(vertx);

		    // All operations done on the observer now can be blocking
		    o = o.observeOn(scheduler);

		    // Load from a blocking api
		    o = o.map(id ->
		            blockingLoad(id)
		    );

		    o.subscribe(item -> {
		      System.out.println("Got item " + item);
		    }, err -> {
		      err.printStackTrace();
		    }, () -> {
		      System.out.println("Done");
		    });*/
		
		

	}

	public static void testRxJava() {
		

		/*
		 * Vertx vertx = Vertx.vertx();
		 * System.out.println("JS Hello World!");
		 * 
		 * HttpServer server = vertx.createHttpServer();
		 * server.requestStream().toObservable().subscribe(req -> {
		 * req.response().putHeader("content-type",
		 * "text/html").end("<html><body><h1>Hello from vert.x!</h1></body></html>"
		 * ); }); server.listen(8080);
		

		EventBus eb = vertx.eventBus();

		eb.consumer(ADDRESS).toObservable().subscribe(message -> {
			System.out.println("Received " + message.body());
			message.reply("PONG");
		});

		// Send a message every second
		vertx.setPeriodic(1000, v -> {
			eb.sendObservable(ADDRESS, "PING").subscribe(reply -> {
				System.out.println("Received reply " + reply.body());
			});
		});
		
		*/ 
		
		try {
			testDCNM();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 

		
	}

	public static void testDCNM() throws Exception, TimeoutException {
		ConnectionFactory factory = new ConnectionFactory();
		System.out.println(" First [*] Waiting for messages. To exit press CTRL+C");

		
		factory.setHost(DCNMHOST);
		factory.setUsername("admin");
		factory.setPassword("cisco123");

		Connection connection = factory.newConnection();
		Channel channel = connection.createChannel();

	
		String queueName = channel.queueDeclare().getQueue();

		/*
		 * if (args.length < 1){
		 * System.err.println("Usage: ReceiveLogsTopic [binding_key]...");
		 * System.exit(1); }
		 * 
		 * for(String bindingKey : args){ channel.queueBind(queueName,
		 * DCNMEXCHANGENAME, bindingKey); }
		 */

		channel.queueBind(queueName , DCNMEXCHANGENAME, "#");
		    

		System.out.println(" [*] Waiting for messages. To exit press CTRL+C");

		QueueingConsumer consumer = new QueueingConsumer(channel);
		channel.basicConsume(queueName, true, consumer);
		//System.out.println("END Hello World!");

		while (true) {
			System.out.println("Get a message   " + numMessages); 
			
			QueueingConsumer.Delivery delivery = consumer.nextDelivery();
			String message = new String(delivery.getBody());
			String routingKey = delivery.getEnvelope().getRoutingKey();

			System.out.println(" [x] Received '" + routingKey + "':'" + message
					+ "'");

			String pattern = "(\\w+)\\.(\\w+)\\.(\\w+)";

			// Create a Pattern object
			Pattern r = Pattern.compile(pattern);

			// Now create matcher object.
			Matcher m = r.matcher(routingKey);

			if (m.find()) {
				System.out.println("Found value: " + m.group(0));
				System.out.println("Found value: " + m.group(1));
				System.out.println("Found value: " + m.group(2));
			} else {
				System.out.println("NO MATCH");
			}

		}

		/*
		 * HttpServer server = vertx.createHttpServer();
		 * 
		 * server.requestHandler(request -> {
		 * 
		 * // This handler gets called for each request that arrives on the //
		 * server HttpServerResponse response = request.response();
		 * response.putHeader("content-type", "text/plain");
		 * 
		 * // Write to the response and end it
		 * response.end("Hello World from the server again !"); });
		 * 
		 * port = 7479;
		 * 
		 * server.listen(port);
		 * 
		 * 
		 * HttpClient client = vertx.createHttpClient(); HttpClientOptions
		 * options = new HttpClientOptions(); //HttpClient client =
		 * vertx.createHttpClient();
		 * 
		 * // Specify both port and host name client.getNow(port, "localhost",
		 * "/", response -> { System.out.println("received status message" +
		 * response.statusMessage());
		 * System.out.println("Received response with status code " +
		 * response.statusCode()); response.bodyHandler(body -> {
		 * System.out.println("Received response body message " +
		 * body.toString()); });
		 * 
		 * });
		 * 
		 * 
		 * // Thread.sleep(1000); vertx.executeBlocking(future -> {
		 * 
		 * }, res -> { System.out.println("The result is: " + res.result()); });
		 * 
		 * server.close();
		 */

	}

	public static void testGenerics() {
		List<Integer> ints = Arrays.asList(1, 2, 3);
		// List<Integer> ints = new ArrayList<Integer>();

		// List<String> words = new ArrayList<String>();
		// List<String> list = new ArrayList<String>;
		int s = 0;

		for (int n : ints) {
			s += n;
		}
		assert s == 6;

		System.out.println("The value is " + s);

	}

}
