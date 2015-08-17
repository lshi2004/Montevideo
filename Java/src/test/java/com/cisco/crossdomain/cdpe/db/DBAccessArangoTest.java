package com.cisco.crossdomain.cdpe.db;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;

import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.unit.Async;
import io.vertx.ext.unit.TestContext;
import io.vertx.ext.unit.junit.VertxUnitRunner;

@RunWith(VertxUnitRunner.class)
public class DBAccessArangoTest {

	private static DBAccess db;
	private static Vertx myVertx = Vertx.vertx();
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		db = new DBAccessArango(myVertx); 
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	/*
	 * Test 1: Test if two different objects in the same collection 
	 * can be created using the same key. In this method, we try to 
	 * create two objects namely group-a and group-b using the same
	 * key value A100.
	 */
	@Test
	public void testCreateSingleCollObject(TestContext context) {

		System.out.println("========================TEST 1: Testing create and store"
				           + " using Arango DB========================");
		
		JsonObject json1 = new JsonObject();
		JsonObject json2 = new JsonObject();
		
		Async async = context.async();
		
		/*
		 * Fill up the JSON object body for the first collection object to be created
		 * and stored in ArangoDB.
		 */
		json1.put("name", "group-a");
		json1.put("description","group A");
		json1.put("endpointPools", "20.1.1.2/8");
		json1.put("conditions", "");
		json1.put("id", "1111");
		json1.put("_key", "A100");
        json1.put("tenant_id", "1");
		
		/*
		 * Fill up JSON object body for the second collection object to be created 
		 * and stored in ArangoDB.
		 */
		json2.put("name", "group-b");
		json2.put("description","group B");
		json2.put("endpointPools", "20.1.1.2/8");
		json2.put("conditions", "");
		json2.put("id", "2222");
		json2.put("_key", "A100");
        json2.put("tenant_id", "1");
		
		db.create(json1.toString(), "epg",  resp -> {
			if (resp.success) {
				System.out.println(" Create passed for Group-A " + resp.body.toString());	
			} else {
				System.out.println("Could not create Group-A since another group has same key!");
			}
			
			/*
			 * If the same key as Json1 is used below the test fails with 
			 * 409 Error code. 
			 */
			Async async2 = context.async();
			db.create(json2.toString(), "epg",  resp1 -> {
				if (resp1.success) {
					System.out.println("Create passed for Group-B" + resp1.body.toString());
				} else {
					System.out.println("Could not create Group-B since another group has same key!");
				}
				
			/*
			 * Clean-up the previously created object.
			 */
			Async async3 = context.async();
			db.delete("A100", "epg", resp2 -> {
				assertEquals(resp2.success, true) ;
				System.out.println("Successfully deleted object with Key A100");
				
				async3.complete();
			});
					
			async2.complete();
			});
			
			async.complete();
		});
		
	}
	
	/*
	 * Test 2: Test if two different objects in different collections
	 * can be created using the same key. In this method, we create two
	 * objects called group-c and rs-a belonging to group and rule_sets 
	 * collections respectively but share the same key C100.
	 */
	@Test
	public void testCreateDiffCollSameKey(TestContext context) {

		System.out.println("========================TEST 2 :Testing create and store different "
				            + "collection objects using same Key========================");
		
		JsonObject json1 = new JsonObject();
		JsonObject json2 = new JsonObject();
		
		Async async = context.async();
		Async async1 = context.async();
		
		/*
		 * Fill up the JSON object body for the first collection object to be created
		 * and stored in ArangoDB.
		 */
		json1.put("name", "group-c");
		json1.put("description","group C");
		json1.put("endpointPools", "20.1.1.2/8");
		json1.put("conditions", "");
		json1.put("id", "3333");
		json1.put("_key", "C100");
        json1.put("tenant_id", "1");
		
		json2.put("name", "rs-a");
		json2.put("description","ruleset A");
		json2.put("endpointPools", "20.1.1.2/8");
		json2.put("custom", "true");
		json2.put("rules", "");
		json2.put("id", "4444");
		json2.put("_key","C100");
        json2.put("tenant_id", "1");
		
		db.create(json1.toString(), "epg",  resp -> {
			assertEquals(resp.success, true); 
			System.out.println("Create passed for Group C with Key C100" + resp.body.toString());
			
			db.create(json2.toString(), "rule_sets",  resp1 -> {
				assertEquals(resp1.success, true); 
				System.out.println("Create passed for Rule-Set A with Key C100" + resp1.body.toString());
				
				Async async2 = context.async();
				db.delete("C100", "epg", resp2 -> {
					assertEquals(resp2.success, true) ;
					System.out.println("Successfully deleted group object with Key C100");
						
						
					Async async3 = context.async();
					db.delete("C100", "rule_sets", resp3 -> {
					assertEquals(resp3.success, true) ;
					System.out.println("Successfully deleted rule_set object with Key C100");
					
					async3.complete();
					});
				async2.complete();
				});
				
			async1.complete();
			});
			
		async.complete();
		});	
	}

	/*
	 * Test 3: Test if a particular object belonging to a collection can
	 * be modified. In this method, we first create a group object called 
	 * group-d and then modify its attributes to that of group-e.
	 */
	@Test
	public void testModify(TestContext context) {
	
		System.out.println("========================TEST 3: Testing modify and store"
				           + " using Arango DB========================");
		
		Async async = context.async();
		
		JsonObject json1 = new JsonObject();
		JsonObject json2 = new JsonObject();
		
		json1.put("name", "group-d");
		json1.put("description","group D");
		json1.put("endpointPools", "20.1.1.2/8");
		json1.put("conditions", "");
		json1.put("id", "5555");
		json1.put("_key", "D100");
        json1.put("tenant_id", "1");
		
		/*
		 * New JSON object for filling new data
		 */
		json2.put("name", "group-e");
		json2.put("description","group E");
		json2.put("endpointPools", "20.1.1.2/8");
		json2.put("conditions", "");
		json2.put("id", "6666");
		json2.put("_key", "D100");
        json2.put("tenant_id", "1");
		
		/*
		 * Create a group collection object.
		 */
		db.create(json1.toString(), "epg",  resp -> {
			assertEquals(resp.success, true); 
			System.out.println("Created Group-D successfully: " + resp.body.toString());
			
			Async async1 = context.async();
			/*
			 * Modify the above group object with the new information.
			 */
		    db.modify(json2.toString(), "epg",  resp1 -> {
		    	assertEquals(resp1.success, true);
		    	System.out.println("Modified Group D to Group E: " + resp1.body.toString());
		    	
		    	Async async2 = context.async();
			    db.get("D100", "epg", resp2 -> {
					assertEquals(resp2.success, true);
					System.out.println("Successfully retrieved object record D100: " + resp2.body.toString());
					
					Async async3 = context.async();
					db.delete("D100", "epg", resp3 -> {
						assertEquals(resp3.success, true) ;
						System.out.println("Successfully deleted modified object with Key D100");
						async3.complete();
					});
					
				async2.complete();
				});
		    	
			async1.complete();		
			});
		   
		async.complete();
		});
	
	}

	/*
	 * Test 4: Test if all objects belonging to a particular collection can be
	 * retrieved. In this test case we try to retrieve all objects belonging to 
	 * the rule_sets collection.
	 */
	@Test
	public void testGetAll(TestContext context) {
		System.out.println("========================TEST 4: Getting all group "
				           + "objects========================");
		
		
		JsonObject json1 = new JsonObject();
		json1.put("name", "Rule1");
		json1.put("description","ruleset 1");
		json1.put("endpointPools", "20.1.1.2/8");
		json1.put("custom", "true");
		json1.put("rules", "");
		json1.put("id", "11111");
		json1.put("_key","RS100");
        json1.put("tenant_id", "1");
	
		/*
		 * Create a sample Rule-Set and then use the getAll method to retrieve all.
		 */
		Async async = context.async();
		db.create(json1.toString(), "rule_sets",  resp -> {
			assertEquals(resp.success, true); 
			System.out.println("Created RuleSet1 successfully: " + resp.body.toString());
			
			Async async2 = context.async();
			db.getAll("1","rule_sets", resp1 -> {
				assertEquals(resp1.success, true) ;
				System.out.println("All rule_sets retrieved successfully!" + resp1.body.toString());
				
				Async async3 = context.async();
				db.delete("RS100", "rule_sets", resp2 -> {
					assertEquals(resp2.success, true) ;
					System.out.println("Successfully deleted object with Key RS100");
					async3.complete();
				});
			
				async2.complete();
			});
			
			async.complete();
		});	
	}

	/*
	 * Test 5: Test if an object belonging to a collection can be deleted
	 * using a key reference to it. In this test method we try to delete 
	 * a sample group object created in the test case for the purpose of 
	 * testing.
	 */
	@Test
	public void testDelete(TestContext context) {
		System.out.println("========================TEST 5: Testing deletion "
				           + "of Object in DB========================");
		JsonObject json1 = new JsonObject();
		json1.put("name", "grp-test-delete");
		json1.put("description","this group is created to test DB delete api");
		json1.put("endpointPools", "20.1.1.2/8");
		json1.put("conditions", "");
		json1.put("id", "7777");
		json1.put("_key", "GD100");
        json1.put("tenant_id", "1");
		
		/*
		 * Create a sample group and then try to delete it.
		 */
		Async async = context.async();
		db.create(json1.toString(), "epg",  resp -> {
			assertEquals(resp.success, true); 
			System.out.println("Created Group GD successfully: " + resp.body.toString());
			
			Async async1 = context.async();
			db.delete("GD100", "epg", resp1 -> {
				assertEquals(resp1.success, true) ;
				System.out.println("Successfully deleted object with Key GD100");
				async1.complete();
			});
		async.complete();
		});	
	}
}
