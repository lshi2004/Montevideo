package com.cisco.crossdomain.cdpe.db;

import java.util.Properties;
import io.vertx.core.Vertx;

import com.cisco.crossdomain.cdpe.db.DBAccess;

public class DBFactory {
	public static DBAccess createDBAccess(Properties prop, Vertx vertx) { 
		String dbType = prop.getProperty("DBType", "Arango"); 
		String dbClass = prop.getProperty("DBClass", "com.cisco.crossdomain.cdpe.db.DBAccessArango"); 
	
		ClassLoader classLoader = DBFactory.class.getClassLoader();
		DBAccess db = null;	
		System.out.println("Now DB is Started DB from " + dbClass);
		
		try {
			Class aClass = classLoader.loadClass(dbClass);
			db = (DBAccess) aClass.getConstructor(Vertx.class).newInstance(vertx); 				
		} catch (Exception e) {
			System.out.println(" Class Not Found" + e.getMessage() + e.getCause());
			e.printStackTrace();
		}

		return db; 
	}
}
