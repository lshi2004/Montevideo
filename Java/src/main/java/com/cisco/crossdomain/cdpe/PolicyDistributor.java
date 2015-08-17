package com.cisco.crossdomain.cdpe;


import java.util.ArrayList;

import com.cisco.crossdomain.cdpe.db.DBAccessArango;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;
import io.vertx.core.eventbus.Message;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.core.json.JsonArray;


public class PolicyDistributor extends AbstractVerticle {
    
    private DBAccessArango   m_dbAccess = null ;
    private ArrayList<DCInfo> m_dcList = new ArrayList<DCInfo>();


    public PolicyDistributor() {

    }

    public void start(Future<Void> startFuture) {
       	m_dbAccess = new DBAccessArango(vertx) ;

    	vertx.eventBus().consumer(EBEvents.POLICY_NB_CRUD, this::handlePolicyCrudEvents);
    	vertx.eventBus().consumer(EBEvents.SRV_NB_CRUD, this::handleServiceCrudEvents);
    	vertx.eventBus().consumer(EBEvents.DC_NB_CRUD, this::handleDomainControllerCrudEvents);
        
        //Read existing DC list from database
        //readAndNotifyExistingDC() ;
    	startFuture.complete();
    }
    
    private void handleDomainControllerCrudEvents(Message<String> message)
    {
        JsonObject msg = new JsonObject(message.body()) ;
        
        
        String action = msg.getString("action") ;
        String dcId = msg.getString("dcId") ;
        System.out.println( "PolicyDistributor: Received DC CRUD event:"+action +" DC id:"+dcId+". Distributing to domain controller plugin") ;
      
        DCInfo dc; 
        if ("add-dc".equals(action)) {
        	dc = new DCInfo(msg); 
            if (!m_dcList.contains(dc)) {
                  m_dcList.add(dc) ;
                  notifyDCEvent(msg.encode()) ;
            }
        }
        else if ("delete-dc".equals(action)) {
            for(int i= 0; i < m_dcList.size(); i++) {
                if (m_dcList.get(i).dcId.equals(dcId)) {
                    m_dcList.remove(i) ;
                    notifyDCEvent(msg.encode()) ;
                    break ;
                }
            }
        }

        

    }
    
    private void handlePolicyCrudEvents(Message<String> message)
    {
    	JsonObject msg = new JsonObject(message.body()) ;
        System.out.println( "PolicyDistributor: Received policy event:"+msg.getString("action") +" Policy id:"+msg.getString("key")+". Distributing to domain controller plugin") ;
        
        //TODO: Resolve policy and identify the DC plugins to send it to
        //      For now, send the same policy to any one
        notifyPolicyEvent(msg.getString("action"), msg.getString("key"), msg.getString("policy")) ;
    }
    
    private void handleServiceCrudEvents(Message<String> message)
    {
    	JsonObject msg = new JsonObject(message.body()) ;
        System.out.println( "PolicyDistributor: Received service event:"+msg.getString("action") +" Service id:"+msg.getString("key")+". Distributing to domain controller plugin") ;
        
        //TODO: Resolve service and identify the DC plugins to send it to
        //      For now, send the same service to any one
        notifyServiceEvent(msg.getString("action"), msg.getString("key"), msg.getString("service")) ;
    }
    
    private void readAndNotifyExistingDC()
    {
    	/*try {
			m_dbAccess.listAllDC( dbresp -> {
				if (dbresp.success) {
					
					JsonArray dcList = new JsonArray(dbresp.body) ;
					for (Object t: dcList) {
						DCInfo dcItem = new DCInfo((JsonObject)t) ;	
						m_dcList.add(dcItem) ;
						notifyDCEvent("add-dc", dcItem.dcId, dcItem.address, dcItem.port);
					}
				}
				else {
					System.out.println("Error retrieving exisint DC list:"+dbresp.statusCode) ;
				}
			});
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}*/
    }

    private void notifyPolicyEvent(String action, String policyKey, String policy)
    {
		JsonObject msg = new JsonObject() ;
		msg.put("action", action) ;
		msg.put("key", policyKey) ;
		msg.put("policy", policy) ;
		vertx.eventBus().send(EBEvents.POLICY_SB_CRUD, msg.encode()) ;
    }
    
    private void notifyServiceEvent(String action, String serviceKey, String service)
    {
		JsonObject msg = new JsonObject() ;
		msg.put("action", action) ;
		msg.put("key", serviceKey) ;
		msg.put("service", service) ;
		vertx.eventBus().send(EBEvents.SRV_SB_CRUD, msg.encode()) ;
    }
    
    private void notifyDCEvent(String action, String dcId, String address, int port)
    {
		JsonObject msg = new JsonObject() ;
		msg.put("action", action) ;
		msg.put("dcId", dcId) ;
		msg.put("address", address) ;
		msg.put("port", port);
    	vertx.eventBus().send(EBEvents.DC_SB_CRUD, msg.encode()) ;
    }

    private void notifyDCEvent(String jsonMessage)
    {
        vertx.eventBus().send(EBEvents.DC_SB_CRUD, jsonMessage) ;
    }

}


