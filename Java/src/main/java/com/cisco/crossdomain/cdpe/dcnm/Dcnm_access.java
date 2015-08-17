package com.cisco.crossdomain.cdpe.dcnm;




import java.net.URI;
import java.util.Base64;

import com.cisco.crossdomain.cdpe.db.DBResponse;

import io.vertx.core.Handler;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.eventbus.Message;
import io.vertx.core.eventbus.MessageConsumer;
import io.vertx.core.http.HttpClient;
import io.vertx.core.http.HttpClientOptions;
import io.vertx.core.http.HttpClientRequest;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.rx.java.RxHelper;
import rx.Observable;
import rx.Subscriber;

public class Dcnm_access {
	 private static final String DCNM_BASIC_AUTH_USER_NAME ="admin";
     private static final String DCNM_BASIC_AUTH_PASSWORD ="cisco123";
     private String DCNM_Token = null;
     //dcnm team testbed
  //   URI uri = URI.create("http://10.193.49.199:80");
     URI uri = URI.create("http://172.27.252.70:80");
     private  HttpClient dcnm_client = null ;
     private  Vertx  vertx = null;
     private EventBus eb = null;
     private String Segmentid_Listening_addr = "wait.for.segmentid";
     
     public Dcnm_access(Vertx vertx, EventBus eb) 
 	 {
         HttpClientOptions options = new HttpClientOptions().setDefaultHost(uri.getHost()).setDefaultPort(uri.getPort());
         options.setKeepAlive(true) ;
         this.vertx = vertx;
         this.eb = eb;
         dcnm_client = vertx.createHttpClient(options);		
 	 }
     
     private static String getBasicAuth() {
    	 if (DCNM_BASIC_AUTH_USER_NAME != null
          && DCNM_BASIC_AUTH_PASSWORD  != null) {
    	  String authinfo = DCNM_BASIC_AUTH_USER_NAME +":"+DCNM_BASIC_AUTH_PASSWORD;
    	  return Base64.getEncoder().encodeToString(authinfo.getBytes());
    	 }
      return null;
     }
     
     public void DCNM_Send(HttpMethod method, String path, JsonObject header, String data, Handler<DCNMResponse> handler) 
 	 {
 		HttpClientRequest creq = dcnm_client.request(method,  path, cresp -> {
 			System.out.println("Send "+method+" request to DCNM "+path+" Received db response with status code " + cresp.statusCode());
 			if (cresp.statusCode() <= 202) {
                 cresp.bodyHandler(new Handler<Buffer>() {
                     public void handle(Buffer body) { 
                         handler.handle(new DCNMResponse(body));
                       }
                   });
           
 			}
 			else {
 				handler.handle(new DCNMResponse(cresp.statusCode(), cresp.statusMessage())) ;
 			}
 		});
 		creq.exceptionHandler(e -> {
 			  System.out.println("Received exception: " + e.getMessage());
 			  e.printStackTrace();
 			});
 		
 		creq.setChunked(false);
 		HeaderHandler(header, creq);
 		if (data!=null) {
 			creq.putHeader("Content-Length", ""+data.length());
 			System.out.println("data "+ data + data.length());
 			creq.end(data) ;
 		} else {
 			creq.end();
 		}
 	}
     public void HeaderHandler(JsonObject header, HttpClientRequest req){
    	 req.putHeader("Content-Type", header.getString("Content-Type"));
    	 if (header.getString("Authorization") != null) {
    		 req.putHeader("Authorization", header.getString("Authorization"));
    	 }	 
    	 if (header.getString("DCNM-Token") != null) {
    		 System.out.println("DCNM token " + header.getString("DCNM-Token"));
    		 req.putHeader("DCNM-Token", header.getString("DCNM-Token"));
    	 }
     }
     
	 public void logon(String Event_addr){
	        JsonObject header = new JsonObject();
	        String data = "expirationTime:3600000";
	        
	        header.put("Content-Type" , "application/json");
	        header.put("Authorization", "Basic " + getBasicAuth());
	        //for starting an observer/observable
	        
	        System.out.println("DCNM logon " + header);
	        DCNM_Send(HttpMethod.POST, "/rest/logon", header, data, dcnmresp -> {
	             if (dcnmresp.success) {
	            	 if (dcnmresp.body!=null) {
	            		 JsonObject json_obj = new JsonObject(dcnmresp.body.toString()) ;
	            		 DCNM_Token  = json_obj.getString("Dcnm-Token");
	            	 }	 
	                 if (DCNM_Token == null) {
	                     System.out.println("Login Error, Null Token" + dcnmresp.body.toString());
	                 }
	                 else {
	                     System.out.println("Login Succeeded" + dcnmresp.body.toString());
	                     eb.publish(Event_addr, "succeeded" );
	                 }
	             }
	             else {
	                 System.out.println("Login Error" + dcnmresp.body.toString()); 
	             }
	        });
	    }
	    /*
	     * This initiates an observer on Event_addr that checks whether token has been passed or not
	     */
	    public void Create_profile_observer(String profilename, String Listening_addr, String Forwarding_addr){
	        if (DCNM_Token != null) {
	            Create_profile(profilename, Forwarding_addr);
                System.out.println("Token is here " + DCNM_Token);
	        } else {
	            MessageConsumer<String> consumer =eb.<String>consumer(Listening_addr);
	            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
	            System.out.println("in create_temp_observer" + Listening_addr);
	        
	            obs.subscribe(new Subscriber<Message<String>>() {
	              @Override
	              public void onNext(Message<String> s) {
	                System.out.println("in create_temp_observer " + s.toString() + s.body());
	                  if(s.body().contains("succeeded"))
	                   {  
	                      unsubscribe();
	                      System.out.println("got the token now can create template "+ s.body());
	                      Create_profile(profilename, Forwarding_addr);
	                   }
	              }
	              @Override
	              public void onCompleted() {
	                // TODO Auto-generated method stub
	                
	              }

	              @Override
	              public void onError(Throwable arg0) {
	                // TODO Auto-generated method stub
	                
	              }
	            });
	        }    
	    }    
	    /*
	     * This api is creating a profile in autoconfig 
	     * The format of the profile has mandatory fields that should be filled as below
	     * 
	     */
	    public void Create_profile(String profilename, String  Forwarding_addr){
	    	 JsonObject header = new JsonObject();
	    	 JsonObject data = new JsonObject();
		        
		     header.put("Content-Type" , "application/json");
		     header.put("DCNM-Token", DCNM_Token);
		     
		     data.put("description", "test");
		     data.put("profileName", profilename);
    		 data.put("profileType","FPVLAN");
		   	 data.put("forwardingMode","anycast-gateway");
		   	 data.put("configCommands","ip access-list acl-$id\n $action $proto1 $ipSrcSubnet1 $ipDestSubnet1 \n vlan $vlanId \n   vn-segment $segmentId \n"  
		   			 +"mode fabricpath\n"  
		   			 +" interface vlan $vlanId \n"
		   			 +" vrf member $vrfName   \n"  
		   			 +" ip address $gatewayIpAddress/$netMaskLength tag 12345   \n"  
		   			 +" ip dhcp relay address $dhcpServerAddr use-vrf $vrfDhcp\n"  
		   			 +"  ipv6 address $gatewayIpv6Address/$prefixLength tag 12345 \n"   
		   			 +"  fabric forwarding mode anycast-gateway \n"  
		   			 +" ip access-group acl-$id in \n"  
		   			 +" no shutdown \n" 
		   			 +" include profile any\n"
		   			 +"!\n");
		     data.put("profileSubType","network:universal");
		     //for starting an observer/observable
		        
		     System.out.println("DCNM logon " + header);
		     //System.out.println("DCNM profile " + data);
		     DCNM_Send(HttpMethod.POST, "/rest/auto-config/profiles/?isFlexCall=tru", header, data.toString(), dcnmresp -> {
		             if (dcnmresp.success) {
		            	 if (dcnmresp.body!=null) {
		            		 System.out.println("Create Profile suceeded " + dcnmresp.body.toString());
		            	 } else {
		            		 System.out.println("Create Profile suceeded " + dcnmresp.body);
		            	 }
		                 eb.publish(Forwarding_addr, "succeeded" );
		             }
		             else {
		                 System.out.println("Create_profile Error might be due to the same profile name " + dcnmresp.toString()); 
		             }
		     });
	    }
	    /*
	     * An observer for policy provisining that first check for the token, and if not there wait for it
	     * It also checks whether net_obj (network object) is filled or not, which if not, it will call for 
	     * finding the correct network object from DCNM 
	     */
	    public void Provision_policy_observer(String Tenant, String Group, String Srcsubnet, String Dstsubnet, String  Protocol, String Port, String Action, JsonObject net_obj, String Logon_Listening_addr){
	    	if (DCNM_Token != null && net_obj != null) {
	    	    Provision_policy_by_segmentId(Tenant, Group, Srcsubnet, Dstsubnet, Protocol,  Port,  Action,  net_obj);
	    	} else if (DCNM_Token == null) {
	            MessageConsumer<String> consumer =eb.<String>consumer(Logon_Listening_addr);
	            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
	            System.out.println("in Provision_policy_observer " + Logon_Listening_addr);
	        
	            obs.subscribe(new Subscriber<Message<String>>() {
	              @Override
	              public void onNext(Message<String> s) {
	                System.out.println("in Provision_policy_observer " + s.toString() + s.body());
	                  if(s.body().contains("succeeded"))
	                   {  
	                      unsubscribe();
	                      System.out.println("got the token now can provision policy "+ s.body());
	      	    	      Provision_policy(Tenant, Group, Srcsubnet, Dstsubnet, Protocol,  Port,  Action,  net_obj);
	                   }
	              }
	              @Override
	              public void onCompleted() {
	                // TODO Auto-generated method stub
	                
	              }

	              @Override
	              public void onError(Throwable arg0) {
	                // TODO Auto-generated method stub
	                
	              }
	            });
	        }  else {
	    	      Provision_policy(Tenant, Group, Srcsubnet, Dstsubnet, Protocol,  Port,  Action,  net_obj);
	        }
	    }
	    /*
	     * An observer that waits for receiving network object by calling Find_network_segmentId
	     */
		public void Provision_policy(String Tenant, String Group, String Srcsubnet, String Dstsubnet, String  Protocol, String Port, String Action, JsonObject net_obj){
			if (net_obj != null) {
	    	    Provision_policy_by_segmentId(Tenant, Group, Srcsubnet, Dstsubnet, Protocol,  Port,  Action,  net_obj);
	    	} else {	    		
	            MessageConsumer<String> consumer =eb.<String>consumer(Segmentid_Listening_addr);
	            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
	            System.out.println("in Provision_policy" + Segmentid_Listening_addr);
	        
	            obs.subscribe(new Subscriber<Message<String>>() {
	              @Override
	              public void onNext(Message<String> s) {
	                System.out.println("in Provision_policy " + s.body());
                    if(s.body().contains("segmentId"))
	                   {  
	                      unsubscribe();
	                      System.out.println("got the network object now can provision policy by segment ID "+ s.body());
	                      JsonObject net_obj = new JsonObject(s.body());
	                      System.out.println("segment " + net_obj.getString("segmentId"));
	      	    	      Provision_policy_by_segmentId(Tenant, Group, Srcsubnet, Dstsubnet, Protocol,  Port,  Action,  net_obj);
	                   }
	              }
	              @Override
	              public void onCompleted() {
	                // TODO Auto-generated method stub
	                
	              }

	              @Override
	              public void onError(Throwable arg0) {
	                // TODO Auto-generated method stub
	                
	              }
	            });
	            Find_network_segmentId(Tenant, Group, Dstsubnet);
	        }  
    	}
		/*
		 * This API, retrieve all the networks associated to organization (tenant), partition (group) in the
		 * DCNM, look inside each network for the dhcp section to match subnet value with the Dstsubnet passed value
		 * if a match found, it will notify and pass that element
		 */
		
		public void Find_network_segmentId(String Tenant, String Group, String Dstsubnet) {
			JsonObject header = new JsonObject();
      	    
      	    header.put("Content-Type" , "application/json");
		    header.put("DCNM-Token", DCNM_Token);
		     
			DCNM_Send(HttpMethod.GET, "/rest/auto-config/organizations/"+Tenant+"/partitions/"+Group+"/networks?detail=true&isFlexCall=true", header, null, dcnmresp -> {
	             if (dcnmresp.success) {
	            	 System.out.println("Find_network_segmendId suceeded " + dcnmresp.body);
	            	 if (dcnmresp.body!=null) {
	            		 JsonArray net_array = new JsonArray(dcnmresp.body.toString());
	            		 for(int i=0;i<net_array.size();i++){
	            			 if(net_array.getJsonObject(i).containsKey("dhcpScope")) {
	            				 JsonObject dhcpscope = net_array.getJsonObject(i).getJsonObject("dhcpScope");
	            			//	 System.out.println("Find_network_segmendId  "+ dhcpscope);
	            				 if (dhcpscope.containsKey("subnet")) {
	            					 System.out.println("Find_network_segmendId  "+ dhcpscope.getString("subnet"));
	            					 if (dhcpscope.getString("subnet").contains(Dstsubnet)) {
	            						 System.out.println("Found dst subnet "+ dhcpscope.getString("subnet"));
	            						 eb.publish(Segmentid_Listening_addr, net_array.getJsonObject(i).toString() );
	            						 return;
	            					 }
	            				 }
	            			 }
	            		 }
	            	 }	 
	            	 // no match found
					 System.out.println("No network found matching dst subnet "+ Dstsubnet);
	            	 eb.publish(Segmentid_Listening_addr, "Failed");
	             }
	             else {
	                 System.out.println("Find setmentId Error" + dcnmresp.body); 
	             }
	        });
		}
		
		/*
		 * Upon finding the corresponding network element to the dstsubnet, this api will be called to
		 * provision policy to incoming direction of dstsubnet network
		 * Important: we should copy all elements of the existing profile of the retrieved network, since it is
		 * working in the overwritting mode
		 */
	    public void Provision_policy_by_segmentId(String Tenant, String Group, String Srcsubnet, String Dstsubnet, String  Protocol, String Port, String Action, JsonObject net_obj){
	    	System.out.println("In Provision_policy_by_segmentId");
	    	JsonObject header = new JsonObject();
	    	JsonObject data = new JsonObject();
		        
		    header.put("Content-Type" , "application/json");
		    header.put("DCNM-Token", DCNM_Token);
		    data.put("profileName",net_obj.getString("profileName"));
		    data.put("vrfName",net_obj.getString("vrfName"));
		    data.put("gateway",net_obj.getString("gateway"));
		    data.put("organizationName",net_obj.getString("organizationName"));
		    data.put("partitionName",net_obj.getString("partitionName"));
		    data.put("netmaskLength",net_obj.getString("netmaskLength"));
		    data.put("networkName",net_obj.getString("networkName"));
		    data.put("segmentId",net_obj.getString("segmentId"));
		    data.put("networkRole",net_obj.getString("networkRole"));
		    data.put("mobilityDomainId",net_obj.getString("mobilityDomainId"));
		    
		    data.put("vlanId",net_obj.getString("vlanId"));
		    data.put("dhcpScope",net_obj.getJsonObject("dhcpScope"));
		    //Should repeat the whole previous config, o.w. it will be nulled
		    // If any constructing elements of the acl is null that means we need to remove the acl
		    if (Protocol == null) {
			    data.put("configArg","$gatewayIpAddress=51.1.1.1;$netMaskLength=24;$gatewayIpAddress/32=;$vlanId=;$segmentId=;$vrfName="+net_obj.getString("vrfName")+";$dhcpServerAddr=;$vrfDhcp=;$gatewayIpv6Address=;$prefixLength=;");
		    } else {
		    	data.put("configArg","$id=client_acl;$ipDestSubnet1="+Dstsubnet+";$proto1="+Protocol+";$ipSrcSubnet1="+Srcsubnet+";$gatewayIpAddress=51.1.1.1;$netMaskLength=24;$gatewayIpAddress/32=;$vlanId=;$segmentId=;$vrfName="+net_obj.getString("vrfName")+";$dhcpServerAddr=;$vrfDhcp=;$gatewayIpv6Address=;$prefixLength=;");
		    }
		    System.out.println("DCNM policy provision header " + header);  
		    System.out.println("DCNM policy provision " + data);
		    DCNM_Send(HttpMethod.POST, "/rest/auto-config/organizations/"+Tenant+"/partitions/"+Group+"/networks/segment/"+net_obj.getString("segmentId")+"?_method=PUT&isFlexCall=true", header, data.toString(), dcnmresp -> {

		             if (dcnmresp.success) {
		            	 System.out.println("Provision_policy_by_segmentId suceeded " + dcnmresp);
		            	 if (dcnmresp.body != null) {
		                     System.out.println("Provision Policy suceeded " + dcnmresp.body.toString());
		            	 }
		             }
		             else {
		                 System.out.println("Policy by segmentid provision Error " + dcnmresp.body); 
		             }
		        });
	    }
}
