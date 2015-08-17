package com.cisco.crossdomain.cdpe.db;

import static org.junit.Assert.*;
import io.vertx.core.json.JsonObject;
import io.vertx.core.json.JsonArray;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class DBAccessMemoryTest {

	private DBAccess db = new DBAccessMemory();


	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {

	}
	
	@Test
	public void testCreateDelete() {
		// add, get
		System.out.println("**************Test testCreateDelete******************");
		JsonObject json1 = new JsonObject();
		json1.put("_key", "M100");
		json1.put("Name", "Larry");
		json1.put("Grade", "Fifth");

		db.create(json1.toString(), "epg",  resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 3); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Larry"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth"); 
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		db.get("M100", "epg", resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 3); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Larry"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth"); 
			System.out.println(" Assert Passed " + resp.body.toString());
		});

		db.delete("M100", "epg", resp -> {
			assertEquals(resp.body, null); 		
		});
	}

	@Test
	public void testModify() {
		// add, get
		System.out.println("**************Test testModify******************");
		JsonObject json1 = new JsonObject();
		json1.put("_key", "M100");
		json1.put("Name", "Larry");
		json1.put("Grade", "Fifth");

		db.create(json1.toString(), "epg",  resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 3); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Larry"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth"); 
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		JsonObject json2 = new JsonObject();
		json2.put("_key", "M100");
		json2.put("Name", "Kelly");
	
		// create entry with existing key should be treated as no-op
		db.create(json2.toString(), "epg",  resp -> {
			assertEquals(resp.body, null); 	
			System.out.println(" Create same entry Rejected as expected ");		
		});
		
		// modify entry needs to take effect 
	    db.modify(json2.toString(), "epg",  resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			System.out.println(" Result returned " + resp.body.toString());	
			assertEquals(jsonOutput.size(), 3); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Kelly"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth"); 
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		db.get("M100", "epg", resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 3); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Kelly"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth"); 
			System.out.println(" Assert Passed " + resp.body.toString());
		});

		db.delete("M100", "epg", resp -> {
			assertEquals(resp.body, null); 		
		});
	}

	
	@Test
	public void testGetAll() {
		// add, get all
		System.out.println("**************Test testGetAll with specific tenants******************");
		
		JsonObject json1 = new JsonObject();
		json1.put("_key", "M100");
		json1.put("Name", "Larry");
		json1.put("Grade", "Fifth");
		json1.put("tenant_id", "1");

		db.create(json1.toString(), "epg",  resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 4); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Larry"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth");
			assertEquals(jsonOutput.getString("tenant_id"), "1");
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		JsonObject json2 = new JsonObject();
		json2.put("_key", "M200");
		json2.put("Name", "Kelly");
		json2.put("Grade", "KinderGarten");
		json2.put("tenant_id", "2");
		
		db.create(json2.toString(), "epg", resp -> {
			System.out.println(" Assert Entered " + resp.body.toString());
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 4); 
			assertEquals(jsonOutput.getString("_key"), "M200"); 
			assertEquals(jsonOutput.getString("Name"), "Kelly"); 
			assertEquals(jsonOutput.getString("Grade"), "KinderGarten");
			assertEquals(jsonOutput.getString("tenant_id"), "2");
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		//Only tenant specific objects should be returned.
		db.getAll("1","epg", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 1);
			System.out.println(" Assert Passed for the number of objects");
			assertEquals(jsonArray.getJsonObject(0).getString("_key"), "M100");
			System.out.println(" Assert Passed for getting the object with key M100");
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
		//Only tenant specific objects should be returned.
		db.getAll("2","epg", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 1);  
			assertEquals(jsonArray.getJsonObject(0).getString("_key"), "M200"); 
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
		db.delete("M100", "epg",  resp -> {
			assertEquals(resp.body, null); 		
		});
		db.delete("M200", "epg",  resp -> {
			assertEquals(resp.body, null); 		
		});
				
	}


	@Test
	public void testMultipleTables() {
		// multiple tables
		System.out.println("**************Test testMultipleTables******************");
		
		JsonObject json1 = new JsonObject();
		json1.put("_key", "M100");
		json1.put("Name", "Larry");
		json1.put("Grade", "Fifth");
		json1.put("tenant_id", "1");

		db.create(json1.toString(), "epg",  resp -> {
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 4); 
			assertEquals(jsonOutput.getString("_key"), "M100"); 
			assertEquals(jsonOutput.getString("Name"), "Larry"); 
			assertEquals(jsonOutput.getString("Grade"), "Fifth");
			assertEquals(jsonOutput.getString("tenant_id"), "1");
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		JsonObject json3 = new JsonObject();
		json3.put("_key", "S200");
		json3.put("Name", "HTTP");
		json3.put("Company", "Cisco");
		json3.put("tenant_id", "2");

		db.create(json3.toString(), "services", resp -> {
			
			JsonObject jsonOutput = new JsonObject(resp.body);
			assertEquals(jsonOutput.size(), 4); 
			assertEquals(jsonOutput.getString("_key"), "S200"); 
			assertEquals(jsonOutput.getString("Name"), "HTTP"); 
			assertEquals(jsonOutput.getString("Company"), "Cisco");
			assertEquals(jsonOutput.getString("tenant_id"), "2");
			System.out.println(" Assert Passed " + resp.body.toString());		
		});
		
		
		db.getAll("1","epg", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 1); 
			assertEquals(jsonArray.getJsonObject(0).getString("_key"), "M100"); 
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
		//Negative test case. No groups should be returned with this tenant id
		db.getAll("2","epg", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 0);  
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
		db.getAll("2","services", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 1); 
			assertEquals(jsonArray.getJsonObject(0).getString("_key"), "S200"); 
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
		//Negative test case. No services should be returned with this tenant id
		db.getAll("1","services", resp -> {
			System.out.println(" Assert All Entered " + resp.body.toString());
			JsonArray jsonArray = new JsonArray(resp.body); 
			
			assertEquals(jsonArray.size(), 0);  
			System.out.println(" Assert Passed " + jsonArray.toString());			
		});
		
	}
	
}
