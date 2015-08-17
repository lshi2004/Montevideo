package com.cisco.crossdomain.cdpe.db;

public class DBResponse 
{
	public int statusCode ;
	public String statusMessage ;
	public String body ;
	public String objectId;
	public boolean success = false ;
	
	public DBResponse(String body, String id) 
	{
		this.success = true ;
		this.body = body;
		this.objectId = id;
	}
	public DBResponse(String body) 
	{
		this.success = true ;
		this.body = body ;
	}
	public DBResponse(int statusCode, String statusMessage) 
	{
		this.success = false ;
		this.statusCode = statusCode ;
		this.statusMessage = statusMessage ;
	}

}
