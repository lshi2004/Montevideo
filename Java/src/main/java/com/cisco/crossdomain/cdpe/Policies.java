package com.cisco.crossdomain.cdpe;

import io.vertx.core.Vertx;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.core.json.JsonArray;
import io.vertx.ext.web.RoutingContext;

import java.time.Instant;
import java.util.UUID;
import java.util.concurrent.atomic.AtomicInteger;

import com.cisco.crossdomain.cdpe.CommonUtil;

public class Policies extends GPE_Collection_Implementation {
	Vertx vertx = null;
	AtomicInteger pol_edge_count_add = new AtomicInteger();
	AtomicInteger pol_edge_count_del = new AtomicInteger();
	JsonArray added_array = null;
	JsonArray removed_array = null;
	HttpServerResponse response = null;
	
	public Policies(Vertx vertx) { 
    	super("policies", "policies");
    	this.vertx = vertx;
    }
    
    public void policyCreateDelete(RoutingContext routingContext) {
    	response = routingContext.response();
		String origin = routingContext.request().getHeader("Origin");	
		
		//Add OPTIONS headers in the response
		CommonUtil.hdlOptionshelper(response, origin);
		
		/*Parse the incoming URI
		  Ex: Incoming URI: /tenants/e48c45d8-5f3d-4408-95e9-d835d731d773/policies
		  	  Tenant id : e48c45d8-5f3d-4408-95e9-d835d731d773		      
		*/
		String relative_uri = routingContext.request().uri();
		//Extract the tenant id.
		String tenant_id = relative_uri.split("/")[2];
		
		JsonObject json_request = routingContext.getBodyAsJson();
		
		removed_array = json_request.getJsonArray("removed");
        added_array = json_request.getJsonArray("added");
        
		pol_edge_count_del.set(removed_array.size());
		pol_edge_count_add.set(added_array.size());
		
		//ConsumerHandler to send the appropriate response to the App.
		//This is called only after the delete and add have been processed. 
		vertx.eventBus().<String>consumer("policy-add", message1 ->{
	    	if(message1.body().contains("succeeded"))
	        {
	    		long unixTimestamp = Instant.now().toEpochMilli();
	    		//Prepare the response
	    		JsonObject json_response = new JsonObject();
	    		json_response.put("added", added_array);
	    		json_response.put("removed", removed_array);
	    		json_response.put("timestamp", unixTimestamp);
	    		
	    		//Send the response
	    		String resp_str = json_response.encode();
	    		response.putHeader("Content-type", "text/plain"); 
	    		response.putHeader("Content-Length", String.valueOf(resp_str.length()));
	    		response.write(resp_str);
	    		response.end();
	        } else if(message1.body().contains("failed")){
	        	//Single response for all failures
	     	    CommonUtil.sendError(404, response);
	        }
		});
		
		//Consumer Handler for delete case listening for policy-delete success or fail.
		//This is called only after the delete is processed. This kicks off the add case.
		vertx.eventBus().<String>consumer("policy-delete", message ->{
	    	if(message.body().contains("succeeded"))
	        {
	    		//Handle the case when there is only delete in the request.
				if (pol_edge_count_add.get() == 0) {
					vertx.eventBus().send("policy-add", "succeeded" );
			    }
				
				//Process each added service-group pair.
				for (int i=0; i< added_array.size(); i++) {
					//Generate the key that is unique to this service<->Group pair.
					UUID id = UUID.randomUUID();
					
					JsonObject added_arr_json = added_array.getJsonObject(i);
					String serviceId = added_arr_json.getValue("serviceId").toString();
					String consumerGroupId = added_arr_json.getValue("consumerGroupId").toString();
					
					added_arr_json.put("_key", String.valueOf(id));
					added_arr_json.put("id", String.valueOf(id));
					added_arr_json.put("tenant_id", tenant_id);
					added_arr_json.put("serviceId", serviceId);
					added_arr_json.put("consumerGroupId", consumerGroupId);
					
					//added_arr_json.remove("added");
					try {
						prepare_create(added_arr_json.encode(), NBAPIService.m_dbAccess, dbresp -> {							
							if (dbresp.success) {
								pol_edge_count_add.set(pol_edge_count_add.decrementAndGet());
								//Send a notification to the add consumer only when all add
								//operations are done. This notification is for sending the response.
								if (pol_edge_count_add.get() == 0) {
									vertx.eventBus().send("policy-add", "succeeded" );
								}
							} else {
								// TODO Need to implement Roll-back here
								//Send a failed notification to the add consumer handler
								System.out.println("Policy add failed for service "
								                    +serviceId+" and Group "+consumerGroupId+" pair");
								vertx.eventBus().send("policy-add", "failed" );
							}
						});
					} catch (Exception e) {
						// TODO Auto-generated catch block
						vertx.eventBus().send("policy-add", "failed" );
						e.printStackTrace();
					}
				}//END for
	        } else if(message.body().contains("failed")){
	     	   vertx.eventBus().send("policy-add", "failed" );
	        }
		});
		
		//Policy delete which calls the handler for policy add consumer handler above, after completion.
		
		//If the removed array is empty, we send a success to the add consumer handler to 
		//proceed with the addition operations.
		if (pol_edge_count_del.get() == 0) {
			vertx.eventBus().send("policy-delete", "succeeded" );
	    }
		
		for (int i=0; i< removed_array.size(); i++) {
			JsonObject removed_arr_json = removed_array.getJsonObject(i);
			String key = removed_arr_json.getString("id");
			String serviceId = removed_arr_json.getValue("serviceId").toString();
			String consumerGroupId = removed_arr_json.getValue("consumerGroupId").toString();
			
			try {
				prepare_delete(key, NBAPIService.m_dbAccess, dbresp -> {							
					if (dbresp.success) {
						pol_edge_count_del.set(pol_edge_count_del.decrementAndGet());
						if (pol_edge_count_del.get() == 0) {
							//Send a notification to the delete consumer to start the add operations.
							vertx.eventBus().send("policy-delete", "succeeded" );
						}
					} else {
						// TODO Need to implement Roll-back here
						System.out.println("Policy delete failed for service "
						                   +serviceId+" and Group "+consumerGroupId+" pair");
						//Send a failed notification to the delete consumer.
						vertx.eventBus().send("policy-delete", "failed" );
					}
				});
			} catch (Exception e) {
				// TODO Auto-generated catch block
				vertx.eventBus().send("policy-delete", "failed" );
				e.printStackTrace();
			}
		}
    }//END policyCreateDelete
    
    public void policyGet(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		
		String origin = routingContext.request().getHeader("Origin");
		CommonUtil.hdlOptionshelper(response, origin);
		
		String http_method = routingContext.request().method().toString().toUpperCase();
	    
		/*Parse the incoming URI
		  Ex: Incoming URI: /tenants/e48c45d8-5f3d-4408-95e9-d835d731d773/policies
		  	  Tenant id : e48c45d8-5f3d-4408-95e9-d835d731d773		      
		*/
		String relative_uri = routingContext.request().uri();
		String[] parsed_uri = relative_uri.split("/");
		
		//Extract the tenant id.
		String tenant_id =  parsed_uri[2];
		
        try {
        		prepare_getAll(tenant_id, NBAPIService.m_dbAccess, dbresp -> {
        			CommonUtil.send_db_response(dbresp, response, http_method);
				});
             } catch (Exception e) {
                       // TODO Auto-generated catch block
                        e.printStackTrace();
                        CommonUtil.sendError(500, response) ;
          }
    }
}
