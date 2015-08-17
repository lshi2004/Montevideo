package com.cisco.crossdomain.cdpe;

import java.util.ArrayList;

import com.cisco.crossdomain.cdpe.db.DBAccessArango;
import com.cisco.crossdomain.cdpe.DCCommunication;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;
import io.vertx.core.eventbus.Message;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;


public class DomainControllerPlugin extends AbstractVerticle {

	private ArrayList<DCInfo> dcList = new ArrayList<DCInfo>();
	private DCCommunication   m_dcAccess = null ;
	
    public DomainControllerPlugin() {
    	System.out.println("Created Controller Plugin");
    }

    public void start(Future<Void> startFuture) {
        vertx.eventBus().consumer(EBEvents.POLICY_SB_CRUD, this::handleCrudEvents);
        vertx.eventBus().consumer(EBEvents.SRV_SB_CRUD, this::handleServiceCrudEvents);
        vertx.eventBus().consumer(EBEvents.DC_SB_CRUD, this::handleDomainControllerCrudEvents);

        m_dcAccess = new DCCommunication(vertx) ;     
        startFuture.complete(); 
    }

    private void handleDomainControllerCrudEvents(Message<String> message)
    {
    	JsonObject msg = new JsonObject(message.body()) ;
        String action = msg.getString("action") ;
        DCInfo dc; 
        
    	System.out.println( "DomainControllerPlugin: Received DC CRUD event:"+msg.getString("action") +" DC id:"+msg.getString("dcId")) ;
        if ("add-dc".equals(action)) {
        	dc = new DCInfo(msg); 
            if (!dcList.contains(dc))
            	dcList.add(dc) ;
        }
        else if ("delete-dc".equals(action)) {
        	for(int i= 0; i < dcList.size(); i++) {
        		if (dcList.get(i).dcId.equals(msg.getString("key"))) {
        			dcList.remove(i) ;
        			break ;
        		}
        	}
        }
        
    }

    
    private void handleCrudEvents(Message<String> message)
    {
    	JsonObject msg = new JsonObject(message.body()) ;
        String action = msg.getString("action") ;
    	System.out.println( "DomainControllerPlugin: Received event:"+msg.getString("action") +" policy id:"+msg.getString("key")) ;
        
        //send it to appropriate domain controller
        if ("add-policy".equals(action)) {
        	handleAddPolicy(msg.getString("key"), msg.getString("policy")) ;
        }
        else if ("delete-policy".equals(action)) {
        	handleDeletePolicy(msg.getString("key")) ;
        }
    }

    
    private void handleServiceCrudEvents(Message<String> message)
    {
    	JsonObject msg = new JsonObject(message.body()) ;
        String action = msg.getString("action") ;
    	System.out.println( "DomainControllerPlugin: Received event:"+msg.getString("action") +" service id:"+msg.getString("key")) ;
        
        //send it to appropriate domain controller
        if ("add-service".equals(action)) {
        	handleAddService(msg.getString("key"), msg.getString("service")) ;
        }
        else if ("delete-service".equals(action)) {
        	handleDeleteService(msg.getString("key")) ;
        }
    }

    
    private void handleAddPolicy(String policyId, String policy) 
    {
    	JsonObject pol = new JsonObject(policy);
		JsonArray arr = pol.getJsonArray("contract");
		
		for ( int j = 0; j < arr.size(); j++)
		{
			for(int i= 0; i < dcList.size(); i++) {
				DCInfo dcInfo = dcList.get(i);
				System.out.println("Traversing DC List -DC Port: " + dcInfo.port+" contract "+arr.getInteger(j)) ;	
				if (dcInfo.port != arr.getInteger(j)) {
					continue;
				}
    		
				try {
					handleAddDCPolicy(dcInfo, policyId, policy) ;
				} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				}
			}
		}
    }
    
    private void handleDeletePolicy(String policyId) 
    {
    	for (DCInfo dcInfo: dcList) {
    		try {
				handleDeleteDCPolicy(dcInfo, policyId) ;
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    	}
    	
    }
    
    private void handleAddDCPolicy(DCInfo dcInfo, String policyId, String policy)  throws Exception
    {
    	JsonObject msg = new JsonObject() ;
    	
		m_dcAccess.createPolicy(dcInfo.address, dcInfo.port, policy, dbresp -> {
			if (dbresp.success) {
				System.out.println("Policy sent to DC:"+dcInfo.address+" port:"+new Integer(dcInfo.port)+" policyId:"+policyId) ;
			}
			else {
				System.out.println("Error sending policy to DC:"+dbresp.statusCode) ;
			}
		});
	
		msg.put("dcId", dcInfo.dcId) ;
		msg.put("policyId", policyId) ;
		System.out.println("Sending Event for "+dcInfo.dcId+" policy "+policyId+"\n") ;
		vertx.eventBus().send(EBEvents.DC_POLICY_MODIFY, msg.encode()) ;
    }
    
    private void handleDeleteDCPolicy(DCInfo dcInfo, String policyId) throws Exception
    {
		m_dcAccess.deletePolicy(dcInfo.address, dcInfo.port, policyId, dbresp -> {
			if (dbresp.success) {
				System.out.println("Policy deleted on DC:"+dcInfo.address+" port:"+new Integer(dcInfo.port)) ;
			}
			else {
				System.out.println("Error Deleting policy on DC:"+dbresp.statusCode) ;
			}
		});
    	
    }
    
    /////////////////////////////////////////////////////////////////////
    
    private void handleAddService(String serviceId, String service) 
    {
    	for (DCInfo dcInfo: dcList) {
    		
    		try {
				handleAddDCService(dcInfo, serviceId, service) ;
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    	}
    }
    private void handleDeleteService(String serviceId) 
    {
    	for (DCInfo dcInfo: dcList) {
    		try {
				handleDeleteDCService(dcInfo, serviceId) ;
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    	}
    	
    }
    private void handleAddDCService(DCInfo dcInfo, String serviceId, String service)  throws Exception
    {
		m_dcAccess.createService(dcInfo.address, dcInfo.port, service, dbresp -> {
			if (dbresp.success) {
				System.out.println("Service sent to DC:"+dcInfo.address+" port:"+new Integer(dcInfo.port)) ;
			}
			else {
				System.out.println("Error sending service to DC:"+dbresp.statusCode) ;
			}
		});
    	
    }
    
    private void handleDeleteDCService(DCInfo dcInfo, String serviceId) throws Exception
    {
		m_dcAccess.deleteService(dcInfo.address, dcInfo.port, serviceId, dbresp -> {
			if (dbresp.success) {
				System.out.println("Service deleted on DC:"+dcInfo.address+" port:"+new Integer(dcInfo.port)) ;
			}
			else {
				System.out.println("Error Deleting service on DC:"+dbresp.statusCode) ;
			}
		});
    	
    }
    
}
