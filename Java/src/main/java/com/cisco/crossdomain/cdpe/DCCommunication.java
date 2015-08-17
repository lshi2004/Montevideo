package com.cisco.crossdomain.cdpe;


import com.cisco.crossdomain.cdpe.db.DBResponse;

import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.http.HttpClient;
import io.vertx.core.http.HttpClientOptions;
import io.vertx.core.http.HttpClientRequest;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.json.JsonObject;

public class DCCommunication {

	private  HttpClient m_client = null ;
	private  Vertx  vertx = null ;
	static {
	
			try {
				init() ;
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}
	
	public DCCommunication(Vertx vertx) 
	{
        HttpClientOptions options = new HttpClientOptions().setDefaultHost("localhost").setDefaultPort(8529);
        options.setKeepAlive(true) ;
        this.vertx = vertx ;
        m_client = vertx.createHttpClient(options);        
		
	}

	
	/*
	 * create policy 
	 */	
	public   void		createPolicy(String dcAddr, int dcPort, String policy, Handler<DBResponse> handler) throws Exception
	{
		HttpClientRequest creq = m_client.request(HttpMethod.POST, dcPort, dcAddr,  "/policies", cresp -> {
			System.out.println("Add Policy. Received db response with status code " + cresp.statusCode());
			if (cresp.statusCode() == 202 || cresp.statusCode() == 200) {
				String strKey = "Key Returned from DC " ;
				System.out.println("Returned document key:"+strKey) ;
				handler.handle(new DBResponse(strKey) );
				//notifyResolver("add-policy", strKey) ;
			}
			else {
				handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
			}
		});
		creq.exceptionHandler(e -> {
			  System.out.println("Received exception: " + e.getMessage());
			  e.printStackTrace();
			});
		
		creq.setChunked(false) ;
	    creq.putHeader("Content-Type", "application/json") ;
	    creq.putHeader("Content-Length", ""+policy.length()) ;
		creq.end(policy) ;
	}
	
	/*
	 * get policy 
	 */	
	public  void		getPolicy(String dcAddr, int dcPort,String key, Handler<DBResponse> handler) throws Exception
	{
		HttpClientRequest creq = m_client.request(HttpMethod.GET, dcPort, dcAddr,  "/policies/"+key, cresp -> {
			System.out.println("Get Policy. Received response with status code " + cresp.statusCode());
			cresp.bodyHandler(body -> {
				if (cresp.statusCode() == 200) {
					handler.handle(new DBResponse(body.toString()) );
				}
				else {
					handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
				}
			});

		});
		creq.end() ;
	}

	/*
	 * delete policy 
	 */	
	public  void		deletePolicy(String dcAddr, int dcPort,String key, Handler<DBResponse> handler) throws Exception
	{
			HttpClientRequest creq = m_client.request(HttpMethod.DELETE, dcPort, dcAddr,  "/policies/"+key, cresp -> {
				System.out.println("Delete Policy. Received response with status code " + cresp.statusCode());
				if (cresp.statusCode() == 200 || cresp.statusCode() == 202) {
					handler.handle(new DBResponse(null) );
				}
				else {
					handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
				}
				//notifyResolver("delete-policy", key) ;

			});
			creq.end() ;
	}

	/*
	 * create service 
	 */	
	public   void		createService(String dcAddr, int dcPort, String service, Handler<DBResponse> handler) throws Exception
	{
		HttpClientRequest creq = m_client.request(HttpMethod.POST, dcPort, dcAddr,  "/services", cresp -> {
			System.out.println("Add Services. Received db response with status code " + cresp.statusCode());
			if (cresp.statusCode() == 202 || cresp.statusCode() == 200) {
				String strKey = "Key returned from DC" ;
				System.out.println("Returned document key:"+strKey) ;
				handler.handle(new DBResponse(strKey) );
			}
			else {
				handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
			}
		});
		creq.exceptionHandler(e -> {
			  System.out.println("Received exception: " + e.getMessage());
			  e.printStackTrace();
			});
		
		creq.setChunked(false) ;
	    creq.putHeader("Content-Type", "application/json") ;
	    creq.putHeader("Content-Length", "" + service.length()) ;
		creq.end(service) ;
	}
	
	/*
	 * get service 
	 */	
	public  void		getService(String dcAddr, int dcPort, String key, Handler<DBResponse> handler) throws Exception
	{
		HttpClientRequest creq = m_client.request(HttpMethod.GET, dcPort, dcAddr,  "/services/"+key, cresp -> {
			System.out.println("Get service. Received response with status code " + cresp.statusCode());
			cresp.bodyHandler(body -> {
				if (cresp.statusCode() == 200) {
					handler.handle(new DBResponse(body.toString()) );
				}
				else {
					handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
				}
			});

		});
		creq.end() ;
	}

	/*
	 * delete policy 
	 */	
	public  void		deleteService(String dcAddr, int dcPort,String key, Handler<DBResponse> handler) throws Exception
	{
			HttpClientRequest creq = m_client.request(HttpMethod.DELETE, dcPort, dcAddr,  "/services/"+key, cresp -> {
				System.out.println("Delete Service. Received response with status code " + cresp.statusCode());
				if (cresp.statusCode() == 200 || cresp.statusCode() == 202) {
					handler.handle(new DBResponse(null) );
				}
				else {
					handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
				}

			});
			creq.end() ;
	}

	
    private static void init() throws Exception {
		// Initialize configure
    }
	
 }
