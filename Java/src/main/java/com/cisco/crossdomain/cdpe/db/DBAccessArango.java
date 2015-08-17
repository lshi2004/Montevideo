package com.cisco.crossdomain.cdpe.db;

import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.http.HttpClient;
import io.vertx.core.http.HttpClientOptions;
import io.vertx.core.http.HttpClientRequest;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

import com.arangodb.ArangoConfigure;
import com.arangodb.ArangoDriver;
import com.arangodb.ArangoException;
import com.arangodb.entity.CollectionEntity;


public class DBAccessArango implements DBAccess {

	
	private static ArangoDriver g_dbdriver = null;
	private static String		g_databaseName = "cdpe" ;
	
	private	static String		g_policyCollectionName = "policies" ;
	private	static String		g_epgCollectionName = "epg" ;
	private	static String		g_epCollectionName = "ep" ;
	private	static String		g_dcCollectionName = "dcontrollers" ;
	private	static String		g_serviceCollectionName = "services" ;
	private	static String		g_classifierCollectionName = "classifiers" ;
	private	static String		g_actionCollectionName = "actions" ;
    private	static String		g_rulesetCollectionName = "rule_sets";
    private static String       g_categoryCollectionName = "categories";
    private static String       g_tenantCollectionName = "tenants";

	private	static CollectionEntity g_policyCollection = null ;
	private	static CollectionEntity g_epgCollection = null ;
	private	static CollectionEntity g_epCollection = null ;
	private	static CollectionEntity g_dcCollection = null ;
	private	static CollectionEntity g_serviceCollection = null ;
	private	static CollectionEntity g_classifierCollection = null ;
    private	static CollectionEntity g_actionCollection = null ;
    private	static CollectionEntity g_rulesetCollection = null ;
    private	static CollectionEntity g_categoryCollection = null ;
    private	static CollectionEntity g_tenantCollection = null ;
    

	
	private  HttpClient m_client = null ;
	private  Vertx  vertx = null ;
	public String temp = new String();
	static {
	
			try {
				initDatabase() ;
			} catch (ArangoException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}
	
	public DBAccessArango(Vertx vertx) 
	{
        HttpClientOptions options = new HttpClientOptions().setDefaultHost("localhost").setDefaultPort(8529);
        options.setKeepAlive(true) ;
        this.vertx = vertx ;
        m_client = vertx.createHttpClient(options);		
        //getAllDCs();
	}
	
	/*
	 * 
	 */
	@Override
	public   void		create(String gpe_obj_Input, String gpe_collection_name, Handler<DBResponse> handler) 
	{
		JsonObject json_obj = new JsonObject(gpe_obj_Input);
		String strKey = json_obj.getString("_key");

		HttpClientRequest creq = m_client.request(HttpMethod.POST,  "/_db/cdpe/_api/document?collection="+gpe_collection_name, cresp -> {
			//System.out.println("Add "+gpe_collection_name+". Received db response with status code " + cresp.statusCode());
			if (cresp.statusCode() == 202) {
                cresp.bodyHandler(new Handler<Buffer>() {
                    public void handle(Buffer body) { 
                        handler.handle(new DBResponse(gpe_obj_Input, strKey) );
                      }
                  });	
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
	    creq.putHeader("Content-Length", ""+gpe_obj_Input.length()) ;
		creq.end(gpe_obj_Input) ;
	}
	
	/*
	 * 
	 */
	@Override
	public  void		modify(String gpe_obj_Input, String gpe_collection_name, Handler<DBResponse> handler) 
	{
		JsonObject json_obj = new JsonObject(gpe_obj_Input) ;
		String strKey  = json_obj.getString("_key");

        HttpClientRequest creq = m_client.request(HttpMethod.PATCH,  "/_db/cdpe/_api/document/"+gpe_collection_name+"/"+strKey, cresp -> {
			//System.out.println("Modify "+gpe_collection_name+". Received db response with status code " + cresp.statusCode());
			if (cresp.statusCode() == 202) {
                cresp.bodyHandler(new Handler<Buffer>() {
                    public void handle(Buffer body) {
                        handler.handle(new DBResponse(gpe_obj_Input, strKey) );
                      }
                  });	
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
	    creq.putHeader("Content-Length", ""+gpe_obj_Input.length()) ;
		creq.end(gpe_obj_Input) ;
	}
	
	/*
	 * 
	 */
	@Override
	public  void		get(String key, String gpe_collection_name, Handler<DBResponse> handler)
	{
		HttpClientRequest creq = m_client.request(HttpMethod.GET, "/_db/cdpe/_api/document/"+gpe_collection_name+"/"+key, cresp -> {
			System.out.println("Get "+gpe_collection_name+". Received response with status code " + cresp.statusCode());
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
	 * 
	 */
	@Override
	public  void		getAll(String tenant_id, String gpe_collection_name, Handler<DBResponse> handler) 
	{
        JsonObject json_obj = new JsonObject() ;
        String query_str = null;
        
        json_obj.put("collection", gpe_collection_name) ;
        if(tenant_id != "all") {
        	//Prepare the query string to include the search attribute as the tenant id4
        	JsonObject json_obj_temp = new JsonObject() ;
        	json_obj_temp.put("tenant_id", tenant_id) ;
        	
        	json_obj.put("example", json_obj_temp) ;
        	//Query string to extract a specific set of documents in a collection from Arango DB
        	//satisfying the search parameters
        	query_str = "/_db/"+g_databaseName+"/_api/simple/by-example";
        } else {
        	query_str = "/_db/"+g_databaseName+"/_api/simple/all";
        }
        
        String body = json_obj.encode();
        
        HttpClientRequest creq = m_client.request(HttpMethod.PUT,  query_str, cresp -> {
            System.out.println("List all "+gpe_collection_name+". Received db response with status code " + cresp.statusCode());
            cresp.bodyHandler(payload -> {
                if (cresp.statusCode() == 200 || cresp.statusCode()==201) {
                    JsonObject res = new JsonObject(payload.toString()) ;
                    JsonArray Listall = res.getJsonArray("result");
                    handler.handle(new DBResponse(Listall.encode()) );
                }
                else {
                    handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
                }
            });
        });
        creq.setChunked(false) ;
        creq.putHeader("Content-Type", "application/json") ;
        creq.putHeader("Content-Length", ""+ body.length()) ;
        creq.end(body) ;
	}
	
	/*
	 * 
	 */
	@Override
	public  void		delete(String key, String gpe_collection_name, Handler<DBResponse> handler) 
	{
			HttpClientRequest creq = m_client.request(HttpMethod.DELETE, "/_db/cdpe/_api/document/"+gpe_collection_name+"/"+key, cresp -> {
				//System.out.println("Delete "+gpe_collection_name+". Received response with status code " + cresp.statusCode());
				if (cresp.statusCode() == 200 || cresp.statusCode() == 202) {
					handler.handle(new DBResponse(null) );
				}
				else {
					handler.handle(new DBResponse(cresp.statusCode(), cresp.statusMessage())) ;
				}
			});
			creq.end() ;
	}
	
    private static ArangoDriver initDatabase() throws ArangoException {
		// Initialize configure
		ArangoConfigure configure = new ArangoConfigure();
		configure.init();

		// Create Driver (this instance is thread-safe)
		// If you use a multi database, you need create each instance.
		ArangoDriver dbdriver = new ArangoDriver(configure); // db = _system    	
		g_dbdriver = dbdriver ;
		try { 
			dbdriver.createDatabase(g_databaseName); 
		  System.out.println("Database created: " + g_databaseName);
		} catch (Exception e) { 
		  //System.out.println("Failed to create database " + g_databaseName + "; " + e.getMessage()); 
		}		
		
		dbdriver.setDefaultDatabase(g_databaseName);
		
		g_epgCollection = createOrGetCollection(g_epgCollectionName) ;
		g_epCollection = createOrGetCollection(g_epCollectionName) ;
		g_dcCollection = createOrGetCollection(g_dcCollectionName) ;
		g_serviceCollection = createOrGetCollection(g_serviceCollectionName) ;
        g_actionCollection = createOrGetCollection(g_actionCollectionName) ;
        g_classifierCollection = createOrGetCollection(g_classifierCollectionName) ;
        g_rulesetCollection = createOrGetCollection(g_rulesetCollectionName) ;
        g_categoryCollection = createOrGetCollection(g_categoryCollectionName) ;
        g_tenantCollection = createOrGetCollection(g_tenantCollectionName) ;
        g_policyCollection = createOrGetCollection(g_policyCollectionName) ;
        
		return dbdriver ;
    }
	
    
    private static CollectionEntity createOrGetCollection(String collectionName) throws ArangoException
    {
    	CollectionEntity collection = null ;
		try {
			  collection = g_dbdriver.createCollection(collectionName);
			  System.out.println("Collection created: " + collection.getName());
		} catch (Exception e) { 
			  collection = g_dbdriver.getCollection(collectionName) ;
			  //System.out.println("Failed to create collection " + collectionName + "; " + e.getMessage()); 
		}		
    	return collection ;
    }
   
}
