package com.montevideo.cisco.tutorial;

import java.io.IOException;

import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.TimeoutException;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.rabbitmq.client.ConnectionFactory;
import com.rabbitmq.client.Connection;
import com.rabbitmq.client.Channel;
import com.rabbitmq.client.ConsumerCancelledException;
import com.rabbitmq.client.QueueingConsumer;
import com.rabbitmq.client.ShutdownSignalException;

class DCNMListenThread extends Thread {

	private static final String DCNMEXCHANGENAME = "DCNMExchange";
	private static final String DCNMHOST = "172.27.252.70";
	static int numDCNMMessages = 0;

	public void run() {
		System.out.println("Hello from a thread!");
		listenDCNMNotification();

	}

	public static void listenDCNMNotification() {
		ConnectionFactory factory = new ConnectionFactory();
		QueueingConsumer consumer = null;

		System.out.println(" DCNM [*] Waiting for messages " + DCNMHOST
				+ " To exit press CTRL+C");

		factory.setHost(DCNMHOST);
		factory.setUsername("admin");
		factory.setPassword("cisco123");

		Connection connection;
		try {
			connection = factory.newConnection();
			Channel channel = connection.createChannel();

			String queueName = channel.queueDeclare().getQueue();
			channel.queueBind(queueName, DCNMEXCHANGENAME, "#");

			consumer = new QueueingConsumer(channel);
			channel.basicConsume(queueName, true, consumer);
		} catch (IOException | java.util.concurrent.TimeoutException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		while (true) {
			System.out.println("Get a message   " + numDCNMMessages);
			numDCNMMessages++;

			QueueingConsumer.Delivery delivery = null;
			try {
				delivery = consumer.nextDelivery();
			} catch (ShutdownSignalException | ConsumerCancelledException
					| InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			String message = new String(delivery.getBody());
			String routingKey = delivery.getEnvelope().getRoutingKey();

			System.out.println(" [x] Received '" + routingKey + "':'" + message
					+ "' from " + Thread.currentThread().getName());

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
	}

}

class OpenStackListenThread extends Thread {

	private static final String STACKEXCHANGENAME = "nova";
	private static final String STACKHOST = "172.27.252.48"; // qos-vm6-2
	static int numStackMessages = 0;

	public void run() {
		System.out.println("Hello from Stack thread!");
		listenStackNotification();

	}

	public static void listenStackNotification() {
		ConnectionFactory factory = new ConnectionFactory();
		QueueingConsumer consumer = null;

		System.out.println(" DCNM [*] Waiting for messages " + STACKHOST
				+ " To exit press CTRL+C");

		// for OpenStack, no username/password is needed
		factory.setHost(STACKHOST);
		// factory.setUsername("admin");
		// factory.setPassword("cisco123");

		Connection connection;
		try {
			connection = factory.newConnection();
			Channel channel = connection.createChannel();

			String queueName = channel.queueDeclare().getQueue();
			channel.queueBind(queueName, STACKEXCHANGENAME, "#");

			consumer = new QueueingConsumer(channel);
			channel.basicConsume(queueName, true, consumer);
		} catch (IOException | java.util.concurrent.TimeoutException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		while (true) {
			System.out.println("Get a message   " + numStackMessages);
			numStackMessages++;

			QueueingConsumer.Delivery delivery = null;
			try {
				delivery = consumer.nextDelivery();
			} catch (ShutdownSignalException | ConsumerCancelledException
					| InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			String message = new String(delivery.getBody());
			String routingKey = delivery.getEnvelope().getRoutingKey();

			System.out.println(" [x] Received '" + routingKey + "':'" + message
					+ "' from " + Thread.currentThread().getName());

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
	}

}

class GPENotificationThread extends Thread {

	private static final String EXCHANGE_NAME = "nova";
	private static final String EXCHANGE_HOST = "localhost";

	public void run() {
		System.out.println("Hello from Stack thread!");
		try {
			sendGPENotification();
		} catch (IOException | TimeoutException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void sendGPENotification() throws IOException, TimeoutException,
			InterruptedException {

		ConnectionFactory factory = new ConnectionFactory();
		factory.setHost(EXCHANGE_HOST);
		Connection connection = factory.newConnection();
		Channel channel = connection.createChannel();

		channel.exchangeDeclare(EXCHANGE_NAME, "topic");

		
		// Policy Creation Events 
		Timer timerPolicyEvent = new Timer();
		timerPolicyEvent.schedule(new TimerTask() {
			int messageCount = 1; 
			
			@Override
			public void run() {
				
				// TODO Auto-generated method stub
				System.out.println("Policy Create Event being Sent");

				String routingKey = "success.com.cisco.cdpe.policy";
				
				String message = " Policy Created messageCount " + messageCount;
				messageCount++; 
				
				if (messageCount % 2 == 0) { 
					message += "Creation"; 
				} else { 
					message += "Deletion"; 
				}

				try {
					channel.basicPublish(EXCHANGE_NAME, routingKey, null,
							message.getBytes());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println(" [x] Sent '" + routingKey + "':'" + message
						+ "'");

			}

		}, 100, 7000);

		
		// Policy Creation Events 
		Timer timerGroupEvent = new Timer();
		timerGroupEvent.schedule(new TimerTask() {
			int messageCount = 1; 
			
			@Override
			public void run() {
				
				// TODO Auto-generated method stub
				System.out.println("Group Create Event being Sent");

				String routingKey = "success.com.cisco.cdpe.group";
				
				String message = " Group Created messageCount " + messageCount;
				messageCount++; 
				
				if (messageCount % 2 == 0) { 
					message += "Creation"; 
				} else { 
					message += "Deletion"; 
				}

				try {
					channel.basicPublish(EXCHANGE_NAME, routingKey, null,
							message.getBytes());
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println(" [x] Sent '" + routingKey + "':'" + message
						+ "'");

			}

		}, 100, 3000);

		
		
		
	}

}

/**
 * Hello world!
 *
 */
public class App {

	public static void main(String[] argv) throws InterruptedException,
			IOException, TimeoutException,
			java.util.concurrent.TimeoutException {

		// DCNMListenThread dcnm = new DCNMListenThread();
		// dcnm.run();

		// OpenStackListenThread openStack = new OpenStackListenThread();
		// openStack.run();

		GPENotificationThread gpeNotify = new GPENotificationThread();
		gpeNotify.run();

		while (true) {
			Thread.sleep(1000);
		}
		
		
		// connection.close();

	}

}
