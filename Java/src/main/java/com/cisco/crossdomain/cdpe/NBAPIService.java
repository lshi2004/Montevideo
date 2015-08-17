package com.cisco.crossdomain.cdpe;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import java.util.UUID;

import com.cisco.crossdomain.cdpe.db.DBAccess;
import com.cisco.crossdomain.cdpe.db.DBFactory;
import com.cisco.crossdomain.cdpe.dcnm.Dcnm_Config_Template;
import com.cisco.crossdomain.cdpe.dcnm.Dcnm_access;
import com.cisco.crossdomain.cdpe.Policies;
import com.cisco.crossdomain.cdpe.CommonUtil;

public class NBAPIService extends AbstractVerticle {
	
	public static DBAccess m_dbAccess = null;
    private int m_listenPort = 8080; 
	private Properties prop = null; 
	private String propFileName = "config/AppNBAPI.properties"; 
	public GPE_Collection_List gpecollection = null;
	private Dcnm_access m_dcnmAccess = null;
    private Dcnm_Config_Template m_dcnmConfigTemp = null;
    public EventBus eb = null;
    //this should be in the observer address class/object
    String Obs_addr = "Observing_Addr.logon";
    //with this we can control whether autoconfig or config template
    private Boolean AUTOCONF = true;
    private String ACL_NAME = "gpedemonew";
    private String TemplateName = "statefarm";
    
	public NBAPIService() {
	}
	
	public NBAPIService(int port, String propFileName) {
		this.m_listenPort = port; 
		this.propFileName = propFileName; 
	}
	
	@Override
	public void start() {
		Router router = Router.router(vertx);

		router.route().handler(BodyHandler.create());
		
		router.post("/auth/login").handler(this::authLogin);
		
		router.get("/tenants").handler(this::listTenants);
		router.get("/tenants/:tenantid/endpoint_pools").handler(this::listEndpoints);
		router.get("/tenants/:tenantid/categories").handler(this::listCategories);
		router.post("/tenants/:tenantid/policies").handler(new Policies(vertx)::policyCreateDelete);
		router.get("/tenants/:tenantid/policies").handler(new Policies(vertx)::policyGet);
		
		router.route().handler(this::commonNBAPI);
		
		//Start the GPE server on port 8080.
		System.out.println("listening port is \n"+m_listenPort) ;
		vertx.createHttpServer().requestHandler(router::accept).listen(m_listenPort);
		
		// Load Properfiles 
		this.prop = new Properties(); 	
		String dir = System.getProperty("user.dir");
		InputStream inputStream = null;
		
		try {
			inputStream = new FileInputStream(dir + "/"+ this.propFileName);
			prop.load(inputStream);			
		} catch (IOException e1) {		
			//property file not existing, just log this 
			//and use default setting
			System.out.println(" Property File not foud " + this.propFileName); 
		} finally {
			if (inputStream != null) {
				try {
					inputStream.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		//for each collection have a different handler for commonNBAPI
		gpecollection = new GPE_Collection_List ();
		
		m_dbAccess = DBFactory.createDBAccess(prop, vertx); 
		eb = vertx.eventBus();
        m_dcnmAccess = new Dcnm_access(vertx,eb);
        m_dcnmConfigTemp = new Dcnm_Config_Template(vertx,eb);
        if (AUTOCONF) {
            /*
             * Steps:
             * 1- logon is mandatory
             * 2- create profile is optional
             * 3- schedule a job for policy provisioning
             * 4- schedule a job for removing acl --> all fields except dstsubnet as shown in the below example 
             * should be null. Currently we only check 5th filed (protocol). 
             */
            m_dcnmAccess.logon(Obs_addr);
            m_dcnmAccess.Create_profile_observer("newgpetest60",  Obs_addr, "wait.profile");
    // tenant, partition (group of provider), 
            m_dcnmAccess.Provision_policy_observer("GPE_Demo", "Sales", "29.1.1.0/24", "51.1.1.0/24", "tcp", "24", "permit", null, Obs_addr);
            /*
             * for removing of the acl from interface and deletion of the access-list
             */
    //      m_dcnmAccess.Provision_policy_observer("GPE_Demo", "Sales", null, "51.1.1.0/24", null, null, null, null, Obs_addr);

        	} else {
        		m_dcnmConfigTemp.logon();
        		m_dcnmConfigTemp.Create_temp_observer(TemplateName);
        		/*
        		 * for port based
        		 */
        		m_dcnmConfigTemp.Create_job_observer(TemplateName, "Ethernet 1/2", ACL_NAME, "29.1.1.21", "51.1.1.23", "0.0.0.255", "0.0.0.255", "deny", "tcp", "23");
        		/*
        		 * for non_port based
        		 */
     //         m_dcnmConfigTemp.Create_job_observer(TempateName, "Ethernet 1/2", ACL_NAME, "29.1.1.21", "51.1.1.23", "0.0.0.255", "0.0.0.255", "deny", "tcp", null);
         /*
          * for removing of the acl from interface and deletion of the access-list
          */
    //          m_dcnmConfigTemp.Create_job_observer(TempateName, "Ethernet 1/2", ACL_NAME, null, null, null, null, null, null, null);
         
 }

	}

	private void authLogin(RoutingContext routingContext) { 
		HttpServerResponse response = routingContext.response();
		String origin = routingContext.request().getHeader("Origin");
		JsonObject json_request = routingContext.getBodyAsJson();
		
		//Generate a unique token for this login.
		UUID token = UUID.randomUUID();
		json_request.put("token", String.valueOf(token));
        json_request.remove("password");
        
        //Prepare the response
        CommonUtil.hdlOptionshelper(response, origin);
		String resp_str = json_request.encode();
		
		response.putHeader("Content-type", "text/plain"); 
        response.putHeader("Content-Length", String.valueOf(resp_str.length()));
		response.write(resp_str);
		response.end();
	}

	private void listEndpoints(RoutingContext routingContext) {
		//System.out.println("Inside the List all endpoints case");
		HttpServerResponse response = routingContext.response();
		
		String origin = routingContext.request().getHeader("Origin");
		CommonUtil.hdlOptionshelper(response, origin);
		
		String relative_uri = routingContext.request().uri();
		String http_method = routingContext.request().method().toString().toUpperCase();
		
		GPE_Collection_Interface gpe_object = null;
	    gpe_object = gpecollection.find(relative_uri);
	    
	    if (gpe_object == null) {	
			System.out.printf("Invalid request for Relative URI: %s and HTTP method: %s\n",
					          relative_uri, http_method);
		}
	    
        try {
        		//Sending "all" for now to show end-points irrespective of their tenant id
        		gpe_object.prepare_getAll("all", m_dbAccess, dbresp -> {
        			CommonUtil.send_db_response(dbresp, response, http_method);
				});
             } catch (Exception e) {
                       // TODO Auto-generated catch block
                        e.printStackTrace();
                        CommonUtil.sendError(500, response) ;
          }
	}
	
	private void listTenants(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		
		String origin = routingContext.request().getHeader("Origin");
		CommonUtil.hdlOptionshelper(response, origin);
		
		String relative_uri = routingContext.request().uri();
		String http_method = routingContext.request().method().toString().toUpperCase();
		
		GPE_Collection_Interface gpe_object = null;
	    gpe_object = gpecollection.find(relative_uri);
	    
	    if (gpe_object == null) {	
			System.out.printf("Invalid request for Relative URI: %s and HTTP method: %s\n",
					          relative_uri, http_method);
		}
	    
        try {
        		gpe_object.prepare_getAll("all", m_dbAccess, dbresp -> {
        			CommonUtil.send_db_response(dbresp, response, http_method);
				});
             } catch (Exception e) {
                       // TODO Auto-generated catch block
                        e.printStackTrace();
                        CommonUtil.sendError(500, response) ;
          }
	}
	
	//TODO: Placeholder for Categories. The App is still populating them for now.
	private void listCategories(RoutingContext routingContext) {
		//System.out.println("Inside the List all categories case");
		HttpServerResponse response = routingContext.response();
		
		String relative_uri = routingContext.request().uri();
		String http_method = routingContext.request().method().toString().toUpperCase();
		
		GPE_Collection_Interface gpe_object = null;
	    gpe_object = gpecollection.find(relative_uri);
	    
	    if (gpe_object == null) {	
			System.out.printf("Invalid request for Relative URI: %s and HTTP method: %s\n",
					          relative_uri, http_method);
		}
	    
	    String origin = routingContext.request().getHeader("Origin");
	    CommonUtil.hdlOptionshelper(response, origin);
		
        try {
        		//Sending "all" for now to show categories irrespective of their tenant id
        		gpe_object.prepare_getAll("all", m_dbAccess, dbresp -> {
        			CommonUtil.send_db_response(dbresp, response, http_method);
				});
             } catch (Exception e) {
                       // TODO Auto-generated catch block
                        e.printStackTrace();
                        CommonUtil.sendError(500, response) ;
          }
	}
	
    //Common API for Policy-provisioning events.
	private void commonNBAPI(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		String origin = routingContext.request().getHeader("Origin");
		boolean request_get_one = false;
		String key = null;
		String http_method = routingContext.request().method().toString().toUpperCase();
		
		//Handle OPTIONS request.
  		if (http_method == "OPTIONS") {
  			CommonUtil.hdlOptions(routingContext);
  			return;
  		}
  		CommonUtil.hdlOptionshelper(response, origin);
  		
		
		/*Parse the incoming URI
		  Ex: Incoming URI: /tenants/e48c45d8-5f3d-4408-95e9-d835d731d773/groups/f7392bcf-a469-40b3-a0b0-ad819a8c2c5b
		  	  Tenant id : e48c45d8-5f3d-4408-95e9-d835d731d773
		      Collection name : groups
		      key :f7392bcf-a469-40b3-a0b0-ad819a8c2c5b
		*/
		String relative_uri = routingContext.request().uri();
		
		String[] parsed_uri = relative_uri.split("/");
		String collection_name = parsed_uri[3];
		
		
		GPE_Collection_Interface gpe_object = null;
	    gpe_object = gpecollection.find(collection_name);
	    
	    if (gpe_object == null) {	
			System.out.printf("Invalid request for Absolute URI: %s and HTTP method: %s\n",
					          relative_uri, http_method);
			CommonUtil.sendError(404, response);
			return;
		}
	    
		
		//Extract the tenant id.
		String tenant_id =  parsed_uri[2];
		
		//Extract the key of the object from the URI, if it exists.
		int length_parsed_uri = parsed_uri.length;
		if (length_parsed_uri > 4) {
			request_get_one = true;
			
			key = parsed_uri[length_parsed_uri -1];
			if (key == null) {
				System.out.println("THe key extracted is NULL");
				CommonUtil.sendError(404, response);
    			return;
    		}
		}
  		
		
		
		
		
		
		try {
			if(http_method == "POST") {
				JsonObject json_request = routingContext.getBodyAsJson();
				
				//Generate the key that is unique to this object.
				UUID id = UUID.randomUUID();
				
				json_request.put("_key", String.valueOf(id));
				json_request.put("id", String.valueOf(id));
				json_request.put("tenant_id", tenant_id);
				
				gpe_object.prepare_create(json_request.encode(), m_dbAccess, dbresp -> {
					CommonUtil.send_db_response(dbresp, response, http_method);
				});
			} else if(http_method == "PATCH") {
				JsonObject json_request = routingContext.getBodyAsJson();
    			json_request.put("_key", key);    			
    			gpe_object.prepare_modify(json_request.encode(), m_dbAccess, dbresp -> {
    				CommonUtil.send_db_response(dbresp, response, http_method);
				});
        		
			} else if(http_method == "GET") {
				if (request_get_one == true) {
					gpe_object.prepare_get(key, m_dbAccess, dbresp -> {
						CommonUtil.send_db_response(dbresp, response, http_method);
					});
				}
				else {
					gpe_object.prepare_getAll(tenant_id, m_dbAccess, dbresp -> {
						CommonUtil.send_db_response(dbresp, response, http_method);
					});
				}
			} else if(http_method == "DELETE") {
				gpe_object.prepare_delete(key, m_dbAccess, dbresp -> {
					CommonUtil.send_db_response(dbresp, response, http_method);
	            });
			} else {
				System.out.println("** Invalid HTTP request **");
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			CommonUtil.sendError(500, response);
		}
    }    

}
