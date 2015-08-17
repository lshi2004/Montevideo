package com.cisco.crossdomain.cdpe.dcnm;

import io.vertx.core.buffer.Buffer;

public class DCNMResponse {
		public int statusCode ;
		public String statusMessage ;
		public Buffer body ;
		public String objectId;
		public boolean success = false ;
		
		public DCNMResponse(Buffer body, String id) 
		{
			this.success = true ;
			this.body = body;
			this.objectId = id;
		}
		public DCNMResponse(Buffer body) 
		{
			this.success = true ;
			this.body = body ;
		}
		public DCNMResponse(int statusCode, String statusMessage) 
		{
			this.success = false ;
			this.statusCode = statusCode ;
			this.statusMessage = statusMessage ;
		}

}
