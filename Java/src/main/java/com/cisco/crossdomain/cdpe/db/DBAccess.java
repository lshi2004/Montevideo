package com.cisco.crossdomain.cdpe.db;

import io.vertx.core.Handler;

public interface DBAccess {
	
	public void create(String content, String collectionName,
			Handler<DBResponse> handler);

	public void delete(String key, String collectionName,
			Handler<DBResponse> handler);

	public void get(String key, String collectionName,
			Handler<DBResponse> handler);

	public void getAll(String tenant_id, String collectionName, Handler<DBResponse> handler);

	public void modify(String content, String collectionName,
			Handler<DBResponse> handler);

}
