/* This class comprises of test case methods to test the GPE code under different 
 * scenarios. The APIs included are the setup and tear-down APIs, the generic 
 * create/delete APIs that can be used for any collection object and finally 
 * the test methods that call the generic APIs as and when needed.
 */

package com.cisco.crossdomain.cdpe.test;

import java.util.UUID;

import io.vertx.core.http.HttpClient;
import io.vertx.core.http.HttpClientRequest;
import io.vertx.core.json.JsonObject;
import io.vertx.core.Handler;

import io.vertx.ext.unit.Async;
import io.vertx.ext.unit.TestContext;
import io.vertx.ext.unit.junit.VertxUnitRunner;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(VertxUnitRunner.class)
public class TestService extends TestCommon {

	private final int serverPort = 9341;
	private HttpClient httpClient = null;
	
	//URI string list
	private final String serviceURI = "/tenants/1/services/";
	private final String groupURI = "/tenants/1/groups";
	private final String classifiersURI = "/tenants/1/classifiers";
	private final String actionsURI = "/tenants/1/actions";
	private final String rulesetURI = "/tenants/1/rule_sets";
	private final String assignmentsURI = "/tenants/1/assignments";
	private final String epURI = "/tenants/1/endpoint_pools";
	
	private final String testServer = "localhost";
	private int serialNumber = 0;

	/* 
	 * Setup API called before any of the test-cases
	 * are executed.
	 */
	@Before
	public  void beforeTest(TestContext context) throws InterruptedException {
		if (httpClient != null) { 
			return; 
		}
		startVerticles(context, serverPort);
		httpClient = getMyVertx().createHttpClient();
	}

	/* This API is called after the test cases are executed.
	 * More like a tear-down API.
	 */
	 
	@After
	public void afterTest(TestContext context) throws InterruptedException {
		if (httpClient != null) { 
			httpClient.close();
		}
		httpClient = null; 
		closeVerticles(context);
	}
	
    //=========================GENERIC API DEFINITIONS====================================
	/*
	 * This is a generic method which can be used to create single service using a user 
	 * defined key,i.e.,this API can be used for the creation of any kind of collection
	 *  object with a user specified key.
	 * Input: User specified key to be put into the JSON object.
	 *        Mock data in form of JSON Object to which the key would be filled in.
	 *        URI specific to a particular object for e.g. group, service, etc.
	 *        Response handler to handle the response to the post request made.
	 * Output: Key value of the newly created collection object with specified 
	 * attributes in the database.
	 */
	String createSingleCollectionObjectWithKey(TestContext context, Async async,
			String key, JsonObject json, String uri, Handler<JsonObject> handler) {
		
		json.put("_key", key);
		HttpClientRequest postReq = httpClient.post(serverPort, testServer,
				                                    uri, resp -> {
			resp.bodyHandler(body -> {
				JsonObject json1 = new JsonObject(body.toString()); 
				handler.handle(json1);
				});
			});

		postReq.headers().add("Content-type", "application/json");
		postReq.end(json.encodePrettily());
		return key;
	}
	
	/*
	 * This is a generic method which can be used to create single service without a user 
	 * defined key.
	 * Input: Mock data in form of JSON Object.
	 *        URI specific to a particular object for e.g. group, service, etc.
	 *        Response handler to handle the response to the post request made.
	 * Output: Key value of the newly created collection object.
	 */
	String createSingleServiceWithoutKey(TestContext context, Async async, JsonObject json,
			                             Handler<JsonObject> handler) {
		UUID id = UUID.randomUUID();
		createSingleCollectionObjectWithKey(context, async, id.toString(), json,
				                            serviceURI, handler);
		return id.toString();
	}
	
	/*
	 * This is a generic method which can be used to delete single service using 
	 * the key as an identifier.
	 * Input: key to be identify the collection object to be deleted.
	 *        URI specific to a particular object for e.g. group, service, etc.
	 *        Response handler to handle the response to the delete request made.
	 * Output: Key value of the deleted collection object.
	 */
	String deleteCollectionObject(TestContext context, Async async, String key,
			                      String uri, Handler<JsonObject> handler){
		HttpClientRequest deleteReq = httpClient.delete(serverPort, testServer,
				uri + "/" + key, resp -> {
					resp.bodyHandler(body -> {
						System.out.println("successfully executed delete string "
										+ key);
						
						LOGGER.info(body.toString());
						handler.handle(null); 
						async.complete();
					});
				});

		deleteReq.end();
		return key;
	}
	
	//=================================TEST SECTION=======================================
	/*
	 * Test 1: Retrieve all services from database.
	 */
	@Test
	public void getAllServicesTest(TestContext context)
			throws InterruptedException {
		
		System.out.println("Getting into Test getAllServicesTest");

		Async async1 = context.async();
		JsonObject json = new JsonObject();
		
		String key = "GetAll" + serialNumber++;
		json.put("name", "Java" + serialNumber++);
		json.put("firstname", "NewInformation");
		json.put("others", "existent objects");
		/*
		 * Call the generic create API where a document gets created under the
		 * appropriate collection using the URI provided as one of the arguments.
		 */
		createSingleCollectionObjectWithKey( context, async1, key, json, serviceURI,
				resp -> {
					String returnKey = resp.getString("_key"); 
					// Send a request and get a response asynchronously
					Async async = context.async();
					httpClient.getNow(serverPort, testServer, serviceURI + 
							          "/" + returnKey, resp1 -> {
					  resp1.bodyHandler(body -> {
					    System.out.println("successfully executed test1 ");
					    LOGGER.info(body.toString());
					    async.complete();
					  });
					});
					System.out.println(" Get All The returned key is " + returnKey); 
					
					//end of processing get All, we are about to delete this
					Async async2 = context.async();
					deleteCollectionObject(context, async2, returnKey, serviceURI,
							               resp2 -> { 
					  System.out.println("Test getAllServicesTest Succeeded  \n\n\n\n");
				    });
					async1.complete();
				});
	}

	/*
	 * Test2: Retrieve service single from database.
	 */
	@Test
	public void getSingleServiceTest(TestContext context) {
		
		System.out.println("Getting into Test getSingleServiceTest");

		Async async1 = context.async();
		String key = "GetSingle0" + serialNumber++;
		JsonObject json = new JsonObject();

		json.put("name", "Java" + serialNumber++);
		json.put("firstname", "NewInformation");
		json.put("others", "existent objects");
		createSingleCollectionObjectWithKey(context, async1, key, json,
				                            serviceURI, resp -> {
					String returnKey = resp.getString("_key"); 
					System.out.println(" Before Get Single The returned key is "
					                   + returnKey); 
					
					// Send a request and get a response asynchronously
					Async async = context.async();
					httpClient.getNow(serverPort, testServer, serviceURI + 
							          "/" + returnKey, resp1 -> {										
					    resp1.bodyHandler(body -> {
						System.out.println("successfully executed retrieval ");
						LOGGER.info(body.toString());
						async.complete();});
										
						System.out.println(" Get Single The returned key is " + returnKey); 
						//end of processing get All, wait for this to complete 
						//we are about to delete this.								
						Async async2 = context.async();
						deleteCollectionObject(context, async2, returnKey, serviceURI, resp2 -> { 
						System.out.println("Test getSingleServiceTest Succeeded \n\n\n\n");
						});			
					});
					async1.complete();
				});
	}

	/*
	 * Test3: Create and delete single service.
	 */
	@Test
	public void createDeleteSingleServiceTest(TestContext context)
			throws InterruptedException {

		System.out.println("Getting into Test createDeleteSingleServiceTest");

		Async async = context.async();
		String key = "Java" + this.serialNumber++;
		JsonObject json = new JsonObject();

		json.put("name", "Java" + this.serialNumber++);
		json.put("firstname", "NewInformation");
		json.put("others", "existent objects");
	
		createSingleCollectionObjectWithKey(context, async,
				                                            key, json, serviceURI, resp -> { 
			// wait for previous request to be flushed first
			//Thread.sleep(300);
			String returnKey = resp.getString("_key"); 
			System.out.println("Key for the collection object created: " + returnKey);
			
			Async async2 = context.async();
			deleteCollectionObject(context, async2, returnKey,serviceURI, resp2 -> { 
				System.out.println("Test deleteCollectionObject Succeeded \n\n\n\n");
			}); 
			async.complete();
		}); 
		
		System.out.println("Test createDeleteSingleServiceTest Succeeded \n\n\n\n");
	}
}
