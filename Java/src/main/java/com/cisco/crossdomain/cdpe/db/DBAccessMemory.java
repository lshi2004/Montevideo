package com.cisco.crossdomain.cdpe.db;

import java.util.HashMap;
import java.util.Map;

import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

class DBMemoryEntry {
	public final String key;
	public final JsonObject json;

	DBMemoryEntry(String key, JsonObject json) {
		this.key = key;
		this.json = json;
	}
}

public class DBAccessMemory implements DBAccess { 
	
	HashMap<String, HashMap<String, DBMemoryEntry>> memDB = new HashMap<>(); 
	
	public DBAccessMemory() { 
		
	}
 
	public DBAccessMemory(Vertx vertx) { 
		
	}
	
	/* 
	 * 
	 */
	@Override 
	public void create(String gpe_obj_Input, String gpe_collection_name, 
			             Handler<DBResponse> handler) 
	{
		JsonObject json_obj = new JsonObject(gpe_obj_Input);
		String strKey = json_obj.getString("_key");

		HashMap<String, DBMemoryEntry> hmap = memDB.get(gpe_collection_name); 
		if (hmap == null) { 
			hmap = new HashMap<String, DBMemoryEntry>(); 
			System.out.println("memDB: Created  entry " + gpe_collection_name); 
			memDB.put(gpe_collection_name, hmap); 
		}	
		
		if (hmap.containsKey(strKey)) { 
			System.out.println("Entry already exists " + strKey); 
			handler.handle(new DBResponse(null));
			return; 
		}
		hmap.put(strKey, new DBMemoryEntry(strKey, json_obj)); 
		System.out.println("Added entry of " + strKey + " to " 
						+ gpe_collection_name + gpe_obj_Input); 
        handler.handle(new DBResponse(json_obj.toString()));
	}
	
	/*
	 * 
	 */
	@Override 
	public void delete(String key, String gpe_collection_name,
			           Handler<DBResponse> handler)
	{	
		HashMap<String, DBMemoryEntry> hmap = memDB.get(gpe_collection_name); 
		if (hmap == null) { 
			//remove non-existent error TBD 
			handler.handle(new DBResponse("Entry Not Found"));
			System.out.println(" memDB: entry not found " + gpe_collection_name); 
			return; 
		}
		
		System.out.println("Removed entry " + key + " from " + gpe_collection_name); 	
		//the expectation is to send null upon deletion 
		handler.handle(new DBResponse(null));
		hmap.remove(key); 
		if (hmap.size() == 0) { 
			System.out.println("memDB: Deleted entry  " + gpe_collection_name); 
			memDB.remove(gpe_collection_name); 			
		}
	}
	
	/*
	 * 
	 */
	@Override 
	public  void get(String key, String gpe_collection_name, 
			         Handler<DBResponse> handler) 
	{
		HashMap<String, DBMemoryEntry> hmap = memDB.get(gpe_collection_name); 
		if (hmap == null || !hmap.containsKey(key)) { 
			System.out.println(" memDB: entry not found " + gpe_collection_name); 
			//remove non-existent error TBD 
			handler.handle(new DBResponse("Entry not found"));
			return; 
		}
		
		DBMemoryEntry entry = hmap.get(key);
		System.out.println("Get entry " + key + entry.json.toString()); 
		// return entry information from entry 
		handler.handle(new DBResponse(entry.json.toString()));
	}

	/*
	 * 
	 */
	@Override 
	public  void getAll(String tenant_id, String gpe_collection_name, Handler<DBResponse> handler) 
	{
		JsonArray json = new JsonArray(); 
		HashMap<String, DBMemoryEntry> hmap = memDB.get(gpe_collection_name); 
		if (hmap == null) { 
			//remove non-existent error TBD 
			System.out.println(" memDB: entry not found " + gpe_collection_name); 
			handler.handle(new DBResponse(" Entry not found "));
			return; 
		}

		hmap.forEach( (k,v) ->{			
			if (v.json.getString("tenant_id").equals(tenant_id)) {
				json.add(v.json);
			}			
		});
		
		System.out.println("Get All entries " + json.toString()); 	
		handler.handle(new DBResponse(json.toString()));
	}
	
	/*
	 * 
	 */
	@Override 
	public void modify(String gpe_obj_Input, String gpe_collection_name, 
			            Handler<DBResponse> handler)
	{
		// handle patch method here to do partial update 
		JsonObject json = new JsonObject(gpe_obj_Input);
		String key = json.getString("_key");

		HashMap<String, DBMemoryEntry> hmap = memDB.get(gpe_collection_name); 
		if (hmap == null || !hmap.containsKey(key)) { 
			System.out.println(" memDB: entry not found " + gpe_collection_name); 
			//remove non-existent error TBD 
			handler.handle(new DBResponse("Entry not found "));
			return; 
		}
		
		System.out.println("Patch " + key + " in collection " + gpe_collection_name); 
		
		JsonObject entry = hmap.get(key).json;
		
		Map<String, Object> map = json.getMap(); 
		
		for (Map.Entry<String,Object> e : map.entrySet()) { 		
			entry.put(e.getKey(), e.getValue()); 
		}
		
		hmap.put(key,  new DBMemoryEntry(key, entry)); 
		
		handler.handle(new DBResponse(entry.toString()));	
	}
	
}