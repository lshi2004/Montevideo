package com.cisco.crossdomain.cdpe;

import com.cisco.crossdomain.cdpe.db.DBResponse;

import io.vertx.core.http.HttpServerResponse;
import io.vertx.ext.web.RoutingContext;

public class CommonUtil {
	public CommonUtil() {
	}
	
	public static void hdlOptionshelper(HttpServerResponse response, String origin) { 
    	if (origin == null) { 
    		origin = "TestDomain"; 
    	}
    	response.putHeader("Access-Control-Allow-Origin", origin);
    	response.putHeader("Access-Control-Allow-Methods", "POST, PATCH, GET, DELETE, OPTIONS");
    	response.putHeader("Access-Control-Allow-Headers", "Content-Type,X-AuthToken ");
    	response.putHeader("Access-Control-Max-Age", "1728000");
    	response.putHeader("Keep-Alive","timeout=2, max=100");
    	response.putHeader("Connection", "Keep-Alive");
    	
    }
    
	public static void hdlOptions(RoutingContext routingContext) { 
		HttpServerResponse response = routingContext.response();
		String origin = routingContext.request().getHeader("Origin");

        hdlOptionshelper(response, origin);
		response.putHeader("Vary", "Accept-Encoding, Origin");
		response.putHeader("Content-Encoding", "gzip");
		response.putHeader("Content-Type", "text/plain");

		sendError(200, response);
	}
	
	public static void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}
	
	public static void send_db_response(DBResponse dbresp, HttpServerResponse response, String http_method) {
		//System.out.println("InSIDE THE SEND_DB_RESPONSE FUNCTION");
		if (http_method == "DELETE") {
			if (dbresp.success) {
				response.end();
			} else {
				CommonUtil.sendError(dbresp.statusCode, response);
			}
		} else {
			if (dbresp.success) {
	            String resp_str = new String(dbresp.body.toString());      
	            response.putHeader("Content-type", "text/plain"); 
	            response.putHeader("Content-Length", String.valueOf(resp_str.length()));
                response.write(resp_str);
                response.end();
			}
			else {
				CommonUtil.sendError(dbresp.statusCode, response) ;
			}
		}
	}
}
