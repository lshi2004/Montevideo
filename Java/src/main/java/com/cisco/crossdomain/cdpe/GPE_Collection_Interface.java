package com.cisco.crossdomain.cdpe;

import com.cisco.crossdomain.cdpe.db.DBAccess;
import com.cisco.crossdomain.cdpe.db.DBResponse;

import io.vertx.core.Handler;

public interface GPE_Collection_Interface {
	public String getCommonName ();
	public String getCollectionName ();
	public void prepare_create(String gpe_obj_Input, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception;
	public void prepare_modify(String gpe_obj_Input, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception;
	public  void prepare_get(String key, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception;
	public  void prepare_getAll(String tenant_id, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception;
	public  void prepare_delete(String key, DBAccess dbaccess, Handler<DBResponse> handler) throws Exception;
}
