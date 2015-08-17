package com.cisco.crossdomain.cdpe;

import com.cisco.crossdomain.cdpe.db.DBAccess;
import com.cisco.crossdomain.cdpe.db.DBResponse;

import io.vertx.core.Handler;


public abstract class GPE_Collection_Implementation implements GPE_Collection_Interface {
	 private String CommonName;
	 private String CollectionName;
		 
     public GPE_Collection_Implementation (String CommonName, String CollectionName) {
		        init(CommonName, CollectionName);
     }

     protected void init(String commonName, String collectionName) {
		        CommonName = commonName;
		        CollectionName = collectionName;
     }
   
     public String getCommonName() { return CommonName; }
     public String getCollectionName() { return CollectionName; }
   
     public void prepare_create(String gpe_obj_Input, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception 
     {

		System.out.println("In create from gpe object: " + CollectionName);
		dbaccess.create(gpe_obj_Input, CollectionName, handler);

   }
     
     public void prepare_modify(String gpe_obj_Input, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception
 	{

 		dbaccess.modify(gpe_obj_Input, CollectionName, handler);
 	}
 	
 	public  void prepare_get(String key, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception
 	{
 		System.out.println("GET" + CollectionName);
 		dbaccess.get(key, CollectionName, handler);
 	}
 	
 	public  void prepare_getAll(String tenant_id, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception
 	{
 		 dbaccess.getAll(tenant_id, CollectionName, handler);
 	}
 	
 	public  void prepare_delete(String key, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception
 	{
 		dbaccess.delete(key, CollectionName, handler);
 	}
}
