package com.cisco.crossdomain.cdpe.db;

import static org.junit.Assert.assertEquals;
import com.cisco.crossdomain.cdpe.db.stressTests; // added to include categories under test
import java.math.*;

import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Observable;

import javax.swing.event.PopupMenuListener;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.experimental.categories.Category;
import org.junit.runner.RunWith;

import io.vertx.core.Vertx;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.eventbus.Message;
import io.vertx.core.eventbus.MessageConsumer;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.unit.Async;
import io.vertx.ext.unit.TestContext;
import io.vertx.ext.unit.junit.VertxUnitRunner;
import io.vertx.rx.java.RxHelper;
import rx.Subscriber;
import rx.observers.*;
import rx.observables.*;


@RunWith(VertxUnitRunner.class)
public class DBAccessArangoStressTest {

	private static DBAccess db;
	private static Vertx myVertx = Vertx.vertx();
	
	float t1 =0; 
	float t2 =0;
	
	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		db = new DBAccessArango(myVertx); 
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception {
	}

	@Before
	public void setUp() throws Exception {
		t1 = returnTimeInSeconds();		
	}

	@After
	public void tearDown() throws Exception {
		t2 = returnTimeInSeconds(); 
		float t_diff = (Float.parseFloat(new DecimalFormat("00.00").format(t2-t1)) -Float.parseFloat("0.06") );
		
		System.out.println("Time to Create, Modify & Delete documents: " + t_diff +" (min.sec)"
				+"\n"+"**********************************************************\n" );

	}
     
	public static float returnTimeInSeconds() {
		
		String timeStamp = new SimpleDateFormat("mm.ss").format(Calendar.getInstance().getTime());		
		return (Float.parseFloat(timeStamp));		
	}

	
	public void testCreateModifyDelete(TestContext context, int scaleNumber, JsonObject inputJson) 
			throws InterruptedException {
	
		System.out.println("Stress TEST : Testing Create, Modify and Delete "+scaleNumber+" docs using Arango DB");
		
		/*
		 * Create a group collection object.
		 */
				
		for (int i = 1; i <= scaleNumber; i++) {
			Async async = context.async();
			inputJson.put("_key", "K"+i);
			db.create(inputJson.toString(), "epg",  resp -> {
				assertEquals(resp.success, true); 
				//System.out.println("Created successfully: " + resp.body.toString());
			async.complete();
			});
		}
		
		
		Thread.sleep(2000);
		
		/*
		 * GetALL group objects created.
		 */
				
			Async async1 = context.async();
				db.getAll(inputJson.toString(), "epg",  resp -> {
					assertEquals(resp.success, true); 
					//System.out.println("Created successfully: " + resp.body.toString());
					async1.complete();
			});
				
		Thread.sleep(2000);
	
		/*
		 * Modify the above group object with the new information.
		 */
				
		for (int i = 1; i <= scaleNumber; i++) {
			Async async2 = context.async();
			inputJson.put("name", "NEW_GROUP");
				db.modify(inputJson.toString(), "epg",  resp -> {
					assertEquals(resp.success, true); 
					//System.out.println("Created successfully: " + resp.body.toString());
					async2.complete();
			});
		}
				
		Thread.sleep(2000);
		
		/*
		 * Delete the above group object 
		 */
				
		for (int i = 1; i <= scaleNumber; i++) {
			Async async3 = context.async();
				db.delete("K"+i, "epg",  resp -> {
					assertEquals(resp.success, true); 
					//System.out.println("Created successfully: " + resp.body.toString());
					async3.complete();
			});
		}
				
}
	
	public JsonObject j100() {
		JsonObject json = new JsonObject();
		json.put("name", "NewGroup");
		json.put("EPP", "20.1.1.2");
		json.put("_key", "");
	    json.put("tenant_id", "1");
	    
	    return json;
	}
	
	public JsonObject j250(){
		JsonObject json = new JsonObject();
		json.put("name", "NewGroup");
		json.put("EPP", "20.1.1.2");
		json.put("_key", "");
        json.put("tenant_id", "1");
        json.put("data", "Policy-map Pmap1 Class-map Cmap1 action Pass Policy-map "
        		+ "Pmap2 Class-map Cmap2 action Drop "
        		+ "Policy-map Pmap3 Class-Default action Pass/Drop");
		
		return json;
	}
	
	public JsonObject j500 () {
		JsonObject json = new JsonObject();
		json.put("name", "NewGroup");
		json.put("EPP", "20.1.1.2");
		json.put("_key", "");
        json.put("tenant_id", "1");
        json.put("data", "Policy-map Pmap1 Class-map Cmap1 action Pass Policy-map "
        		+ "Pmap2 Class-map Cmap2 action Drop "
        		+ "Policy-map Pmap3 Class-Default action Pass/Drop"
        		+ "Pmap3 Class-map Cmap3 action Drop "
        		+ "Policy-map Pmap4 Class-Default action Pass/Drop"
        		+ "Pmap4 Class-map Cmap4 action Drop "
        		+ "Policy-map Pmap5 Class-Default action Pass/Drop"
        		+ "Pmap5 Class-map Cmap5 action Drop "
        		+ "Policy-map Pmap6 Class-Default action Pass/Drop"
        		+ "Class-map");
		
		return json;
	}
	
	public JsonObject j750 () {
		JsonObject json = new JsonObject();
		json.put("name", "NewGroup");
		json.put("EPP", "20.1.1.2");
		json.put("_key", "");
        json.put("tenant_id", "1");
        json.put("data", "Policy-map Pmap1 Class-map Cmap1 action Pass Policy-map "
        		+ "Pmap2 Class-map Cmap2 action Drop "
        		+ "Policy-map Pmap3 Class-Default action Pass/Drop"
        		+ "Pmap3 Class-map Cmap3 action Drop "
        		+ "Policy-map Pmap4 Class-Default action Pass/Drop"
        		+ "Pmap4 Class-map Cmap4 action Drop "
        		+ "Policy-map Pmap5 Class-Default action Pass/Drop"
        		+ "Pmap5 Class-map Cmap5 action Drop "
        		+ "Policy-map Pmap6 Class-Default action Pass/Drop"
        		+ "Pmap3 Class-map Cmap3 action Drop "
        		+ "Policy-map Pmap4 Class-Default action Pass/Drop"
        		+ "Pmap4 Class-map Cmap4 action Drop "
        		+ "Policy-map Pmap5 Class-Default action Pass/Drop"
        		+ "Pmap5 Class-map Cmap5 action Drop "
        		+ "Policy-map Pmap6 Class-Default action Pass/Drop"
        		+ "Class-map CMAP");
		return json;
	}

	// Begin tests with byte size 100
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes100Num100(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j100();
        System.out.println("Document Size = 100 Bytes, Number = 100");
        testCreateModifyDelete(context, 100, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes100Num1000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j100();
        System.out.println("Document Size = 100 Bytes, Number = 1000");
        testCreateModifyDelete(context, 1000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes100Num10000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j100();
        System.out.println("Document Size = 100 Bytes, Number = 10000");
        testCreateModifyDelete(context, 10000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes100Num25000(TestContext context) throws InterruptedException {   
		JsonObject json1 = new JsonObject();
	    json1 = this.j100();    
        System.out.println("Document Size = 100 Bytes, Number = 25000");
        testCreateModifyDelete(context, 25000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes100Num50000(TestContext context) throws InterruptedException {       
		JsonObject json1 = new JsonObject();
	    json1 = this.j100();	    
        System.out.println("Document Size = 100 Bytes, Number = 50000");
        testCreateModifyDelete(context, 50000, json1);
	}
	
	// Begin tests with byte size 250
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes250Num100(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j250();
        System.out.println("Document Size = 250 Bytes, Number = 100");
        testCreateModifyDelete(context, 100, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes250Num1000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j250();
        System.out.println("Document Size = 250 Bytes, Number = 1000");
        testCreateModifyDelete(context, 1000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes250Num10000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j250();
        System.out.println("Document Size = 250 Bytes, Number = 10000");
        testCreateModifyDelete(context, 10000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes250Num25000(TestContext context) throws InterruptedException {   
		JsonObject json1 = new JsonObject();
	    json1 = this.j250();    
        System.out.println("Document Size = 250 Bytes, Number = 25000");
        testCreateModifyDelete(context, 25000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes250Num50000(TestContext context) throws InterruptedException {       
		JsonObject json1 = new JsonObject();
	    json1 = this.j250();	    
        System.out.println("Document Size = 250 Bytes, Number = 50000");
        testCreateModifyDelete(context, 50000, json1);
	}
	
	
	// Begin tests with byte size 500
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes500Num100(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j500();
        System.out.println("Document Size = 500 Bytes, Number = 100");
        testCreateModifyDelete(context, 100, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes500Num1000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j500();
        System.out.println("Document Size = 500 Bytes, Number = 1000");
        testCreateModifyDelete(context, 1000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes500Num10000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j500();
        System.out.println("Document Size = 500 Bytes, Number = 10000");
        testCreateModifyDelete(context, 10000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes500Num25000(TestContext context) throws InterruptedException {   
		JsonObject json1 = new JsonObject();
	    json1 = this.j500();    
        System.out.println("Document Size = 500 Bytes, Number = 25000");
        testCreateModifyDelete(context, 25000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes500Num50000(TestContext context) throws InterruptedException {       
		JsonObject json1 = new JsonObject();
	    json1 = this.j500();	    
        System.out.println("Document Size = 500 Bytes, Number = 50000");
        testCreateModifyDelete(context, 50000, json1);
	}	
	
	// Begin tests with byte size 750
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes750Num100(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j750();
        System.out.println("Document Size = 750 Bytes, Number = 100");
        testCreateModifyDelete(context, 100, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes750Num1000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j750();
        System.out.println("Document Size = 750 Bytes, Number = 1000");
        testCreateModifyDelete(context, 1000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes750Num10000(TestContext context) throws InterruptedException {
		JsonObject json1 = new JsonObject();
	    json1 = this.j750();
        System.out.println("Document Size = 750 Bytes, Number = 10000");
        testCreateModifyDelete(context, 10000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes750Num25000(TestContext context) throws InterruptedException {   
		JsonObject json1 = new JsonObject();
	    json1 = this.j750();    
        System.out.println("Document Size = 750 Bytes, Number = 25000");
        testCreateModifyDelete(context, 25000, json1);
	}
	
	@Test
	@Category({ stressTests.class })
	public void testDocBytes750Num50000(TestContext context) throws InterruptedException {       
		JsonObject json1 = new JsonObject();
	    json1 = this.j750();	    
        System.out.println("Document Size = 750 Bytes, Number = 50000");
        testCreateModifyDelete(context, 50000, json1);
	}	
	
	
}
