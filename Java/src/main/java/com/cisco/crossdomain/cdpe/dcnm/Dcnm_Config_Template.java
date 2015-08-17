package com.cisco.crossdomain.cdpe.dcnm;

import java.net.URI;
import java.util.Base64;

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

public class Dcnm_Config_Template {
	private static final String DCNM_BASIC_AUTH_USER_NAME ="admin";
    private static final String DCNM_BASIC_AUTH_PASSWORD ="cisco123";
    private String DCNM_Token = null;
    //172.27.252.70 & 172.27.252.69, GPE's team testbed
    URI uri = URI.create("http://172.27.252.70:80");
    private  HttpClient dcnm_client = null ;
    private  Vertx  vertx = null;
    private EventBus eb = null;
    private String Logon_addr = "wait.for.token";
    private String Create_template_addr = "wait.for.temp.create";
    private String Delete_template_addr = "wait.for.temp.delete";
    
    public Dcnm_Config_Template(Vertx vertx, EventBus eb) 
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
    
	 public void logon(){
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
	                     //do something//
	                 }
	                 else {
	                     System.out.println("Login Succeeded" + dcnmresp.body.toString());
	                     eb.publish(Logon_addr, "succeeded" );
	                 }
	             }
	             else {
	                 System.out.println("Login Error" + dcnmresp.body.toString()); 
	             }
	        });
	    }
	/*
     * This initiates an observer on Event_addr that checks whether token has been passed or not
     * We should first delete the existing templatename, add a new one
     * create templates for 
     *  1- $action $protocol $source/$mask $dst/$mask eq $port
     *  2- $action ip $source/$mask $dst/$mask
     *  3- removal of acl
     */
	    public void Create_temp_observer(String templatename){
	        if (DCNM_Token != null) {
	            Create_template(templatename);
               System.out.println("Token is here " + DCNM_Token);
	        } else {
	            MessageConsumer<String> consumer =eb.<String>consumer(Logon_addr);
	            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
	            System.out.println("in create_temp_observer" + Logon_addr);
	        
	            obs.subscribe(new Subscriber<Message<String>>() {
	              @Override
	              public void onNext(Message<String> s) {
	                System.out.println("in create_temp_observer " + s.toString() + s.body());
	                  if(s.body().contains("succeeded"))
	                   {  
	                      unsubscribe();
	                      System.out.println("got the token now can create template "+ s.body());
	                      Create_template(templatename);
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
	     * If we create the same template name again, it will give error, so 
	     * for now, we delete the templates first then recreate them.
	     * Create templates for general case:
	     * $action $protocol $source $mask $dst $mask eq $port
	     * for non_port case:
	     * $action $protocol $source/$mask $dst/$mask
	     * for removal:
	     * int e 1/2
	     *   no ip access-group $name in
	     * no ip access-list $name
	     */
	    public void Create_template(String templatename){
	    	Delete_templates(templatename+"_port");
	    	Delete_templates(templatename+"_no_port");
	    	Delete_templates(templatename+"_removal");
	    	
	    	MessageConsumer<String> consumer =eb.<String>consumer(Delete_template_addr);
            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
            System.out.println("in create_temp_observer" + Delete_template_addr);
            
            obs.subscribe(new Subscriber<Message<String>>() {
            	  int delete = 0;
	              @Override
	              public void onNext(Message<String> s) {
	                System.out.println("in create template " + s.toString() + s.body());
	                  if(s.body().contains("succeeded"))
	                   {  delete++;
	                      if (delete==3) {
	                      System.out.println(" now can create template "+ s.body());
	                      unsubscribe();
	                      Create_template_general(templatename+"_port");
	              	      Create_template_no_port(templatename+"_no_port");
	              	      Create_template_removal(templatename+"_removal");
	                      }
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
	    
	    public void Delete_templates(String templatename){
	    	JsonObject header = new JsonObject();
	    	header.put("Content-Type" , "application/json");
		    header.put("DCNM-Token", DCNM_Token);
		    DCNM_Send(HttpMethod.DELETE, "/fmrest/config/templates/"+ templatename, header, null, dcnmresp -> {
	             if (dcnmresp.success) {
	                 System.out.println("Delete template "+ templatename +" suceeded " + dcnmresp.body);
	                 
	                 eb.publish(Delete_template_addr, "succeeded" );
	             }
	             else {
	                 System.out.println("Delete_templates Error " + dcnmresp.toString()); 
	             }
	        }); 
	    }
	    
	    /*
	     * Create port-based template
	     */
	    public void Create_template_general(String templatename){
	    	 JsonObject header = new JsonObject();
		        
		     header.put("Content-Type" , "text/plain");
		     header.put("DCNM-Token", DCNM_Token);
		     String template = "##template properties\n";
		     template = template + "name =" + templatename+ ";\n";
		     template = template + "description = test app description;\n";
		     template = template + "userDefined= true;\n";
		     template = template + "supportedPlatforms = All;\n";
		     template = template + "templateType = CLI;\n";
		     template = template + "published = false;\n";
		     template = template + "timestamp = 2015-08-06 05:43:21;\n";
		     template = template + "##\n";
		     template = template + "##template variables\n";
    		 template = template + "interfaceRange INTERNAL_IFS;\n";
    		 template = template + "string ACLNAME;\n";
    		 template = template + "ipV4Address SRCIPV44;\n";
    		 template = template + "ipV4Address DSTIPV4;\n";
    		 template = template + "ipV4Address SRCMASK;\n";
    		 template = template + "ipV4Address DSTMASK;\n";
    		 template = template + "string ACTION;\n";
    		 template = template + "string PROTO;\n";
    		 template = template + "integer PORT;\n";
    		 template = template + "##\n";
    		 template = template + "##template content\n";
    		 template = template + "ip access-list $$ACLNAME$$\n";
    		 template = template + "$$ACTION$$ $$PROTO$$ $$SRCIPV44$$ $$SRCMASK$$ $$DSTIPV4$$ $$DSTMASK$$ eq $$PORT$$\n";
    		 template = template + "interface $$INTERNAL_IFS$$\n";
  			 template = template + "ip access-group $$ACLNAME$$  in\n";
    		 template = template + "##\n";
		     System.out.println("DCNM logon " + header);
		     System.out.println("DCNM profile " + template);
	         DCNM_Send(HttpMethod.POST, "/fmrest/config/templates", header, template, dcnmresp -> {
		             if (dcnmresp.success) {
		            	 if (dcnmresp.body != null) {
		            		 System.out.println("Create Profile suceeded " + dcnmresp.body.toString());
		            	 } else {
		            		 System.out.println("Create Profile suceeded " + dcnmresp.body);
		            	 }		            	 
		                 eb.publish(Create_template_addr, "succeeded" );
		             } else {
	            		 System.out.println("Create_profile Error, might be due to the same template name " + templatename + " "+ dcnmresp.body);
		             }
		        });
	    }
	    
	    /*
	     * Create non-port-based template
	     */
	    public void Create_template_no_port(String templatename){
	    	 JsonObject header = new JsonObject();
		        
		     header.put("Content-Type" , "text/plain");
		     header.put("DCNM-Token", DCNM_Token);
		     String template = "##template properties\n"
		      + "name =" + templatename+ ";\n"
		      + "description = test app description;\n"
		      + "userDefined= true;\n"
		      + "supportedPlatforms = All;\n"
		      + "templateType = CLI;\n"
		      + "published = false;\n"
		      + "timestamp = 2015-08-06 05:43:21;\n"
		      + "##\n";
		     template = template + "##template variables\n"
   		      + "interfaceRange INTERNAL_IFS;\n"
   		      + "string ACLNAME;\n"
   		      + "ipV4Address SRCIPV4;\n"
   		      + "ipV4Address DSTIPV4;\n"
   		      + "ipV4Address SRCMASK;\n"
   		      + "ipV4Address DSTMASK;\n"
   		      + "string ACTION;\n"
   		      + "string PROTO;\n"
   		      + "##\n";
   		      template = template + "##template content\n"
   		      + "ip access-list $$ACLNAME$$\n"
   		      + "$$ACTION$$ $$PROTO$$ $$SRCIPV4$$ $$SRCMASK$$ $$DSTIPV4$$ $$DSTMASK$$\n"
   		      + "interface $$INTERNAL_IFS$$\n"
 			  + "ip access-group $$ACLNAME$$  in\n"
   		      + "##\n";
		     System.out.println("DCNM logon " + header);
		     System.out.println("DCNM profile " + template);
	         DCNM_Send(HttpMethod.POST, "/fmrest/config/templates", header, template, dcnmresp -> {
	        	 if (dcnmresp.success) {
	            	 if (dcnmresp.body != null) {
	            		 System.out.println("Create Profile suceeded " + dcnmresp.body.toString());
	            	 } else {
	            		 System.out.println("Create Profile suceeded " + dcnmresp.body);
	            	 }
	            	 
	                 eb.publish(Create_template_addr, "succeeded" );
	             } else {
	            		 System.out.println("Create_profile Error, might be due to the same template name " + templatename + " "+ dcnmresp.body);
		         }
		        });
	    }
	    
	    /*
	     * Create template for removing acl
	     */ 
	    public void Create_template_removal(String templatename){
	    	 JsonObject header = new JsonObject();
		        
		     header.put("Content-Type" , "text/plain");
		     header.put("DCNM-Token", DCNM_Token);
		     String template = "##template properties\n"
		       + "name =" + templatename+ ";\n"
		       + "description = ACL removal template;\n"
		       + "userDefined= true;\n"
		       + "supportedPlatforms = All;\n"
		       + "templateType = CLI;\n"
		       + "published = false;\n"
		       + "timestamp = 2015-08-06 05:43:21;\n"
		       + "##\n";
		     template = template + "##template variables\n"
   		       + "interfaceRange INTERNAL_IFS;\n"
   		       + "string ACLNAME;\n"
   		       + "##\n";
   		     template = template + "##template content\n"
   		     + "interface $$INTERNAL_IFS$$\n"
 			 + "no ip access-group $$ACLNAME$$ in\n"
   		     + "no ip access-list $$ACLNAME$$\n"
   		     + "##\n";
		     System.out.println("DCNM logon " + header);
		     System.out.println("DCNM profile " + template);
	         DCNM_Send(HttpMethod.POST, "/fmrest/config/templates", header, template, dcnmresp -> {
	        	 if (dcnmresp.success) {
	            	 if (dcnmresp.body != null) {
	            		 System.out.println("Create Profile suceeded " + dcnmresp.body.toString());
	            	 } else {
	            		 System.out.println("Create Profile suceeded " + templatename + " "+ dcnmresp.body);
	            	 }
	            	 
	                 eb.publish(Create_template_addr, "succeeded" );
		         } else {
		                 System.out.println("Create_profile Error, might be due to the same template name " + dcnmresp.toString()); 
		         }
		        });
	    }
	    /*
	     * This initiates an observer on Event_addr that checks whether token has been passed or not
	     */
	    public void Create_job_observer(String templatename, String Interface, String ACLname, String SRCIP, String DSTIP, String SRCMask, String DSTMask, String Action, String Protocol, String Port) {
		        if (DCNM_Token != null) {
		        	Schedule_template_push( templatename, Interface, ACLname, SRCIP, DSTIP, SRCMask, DSTMask, Action, Protocol, Port);
 	                System.out.println("Token is here " + DCNM_Token);
		        } else {
		            MessageConsumer<String> consumer =eb.<String>consumer(Logon_addr);
		            
		            Observable<Message<String>> obs = RxHelper.toObservable(consumer);
		            System.out.println("in create_temp_observer" + Logon_addr);
		        
		            obs.subscribe(new Subscriber<Message<String>>() {
		              @Override
		              public void onNext(Message<String> s) {
		                System.out.println("in create_temp_observer " + s.toString() + s.body());
		                  if(s.body().contains("succeeded"))
		                   {  
		                      unsubscribe();
		                      System.out.println("got the token now can schedule the job, response: "+ s.body());
 		  		        	  Validate_template_push( templatename, Interface, ACLname, SRCIP, DSTIP, SRCMask, DSTMask, Action, Protocol, Port);

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
		 * Checks whether templatename is existed in the dcnm templates or not, if now initiate 
		 * an observer to fire once the template has been created.
		 */
	    public void Validate_template_push(String templatename, String Interface, String ACLname, String SRCIP, String DSTIP, String SRCMask, String DSTMask, String Action, String Protocol, String Port){
	    	JsonObject header = new JsonObject();
		        
	    	header.put("Content-Type" , "text/plain");
		    header.put("DCNM-Token", DCNM_Token);
		    String template = templatename;
		    if (Protocol == null) {
		   		template = templatename + "_removal";
		   	} else if (Port != null) {
		   			 template = templatename + "_port";
		   	} else {
		   			 template = templatename + "_no_port";
		   	}
	    	DCNM_Send(HttpMethod.GET, "/fmrest/config/templates/"+template, header, null, dcnmresp -> {
	             if (dcnmresp.success) {
	                 System.out.println("Template is already created " + dcnmresp.body.toString());
	                 Schedule_template_push( templatename, Interface, ACLname, SRCIP, DSTIP, SRCMask, DSTMask, Action, Protocol, Port);

	             }
	             else {
	                 System.out.println("Template is not existed, start an observer " + dcnmresp.toString()); 
	                 MessageConsumer<String> consumer =eb.<String>consumer(Create_template_addr);
			         Observable<Message<String>> obs = RxHelper.toObservable(consumer);
			         System.out.println("Observer for " + Create_template_addr);
			        
			         obs.subscribe(new Subscriber<Message<String>>() {
			         @Override
			         public void onNext(Message<String> s) {
			            System.out.println("in create_temp_observer " + s.toString() + s.body());
			            if(s.body().contains("succeeded"))
			                   {  
			                      unsubscribe();
			                      System.out.println("Template created now can schedule the job, response: "+ s.body());
			                      Schedule_template_push( templatename, Interface, ACLname, SRCIP, DSTIP, SRCMask, DSTMask, Action, Protocol, Port);

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
	        });
	    }
	    /*
	     * Assumtpion is if removal is requested only Interface and ACLname are provided
	     * if non port-based acl is requested, the format will be:
	     * $action $protocol $source $mask $dst $mask
	     * if port-based acl is requested, the format is:
	     * $action $protocol $source $mask $dst $mask eq $port
	     */
	    
	    public void Schedule_template_push(String templatename, String Interface, String ACLname, String SRCIP, String DSTIP, String SRCMask, String DSTMask, String Action, String Protocol, String Port){
	    	 JsonObject header = new JsonObject();
	    	 JsonObject data = new JsonObject();
		        
		     header.put("Content-Type" , "application/json");
		     header.put("DCNM-Token", DCNM_Token);
		     
		     data.put("description", "test");
		     data.put("timeout", "30");
    		 data.put("taskEnabled","true");
		   	 data.put("scheduledTimeStr","04/07/2015 22:52:00:00");
		   	 data.put("configDeliveryTaskRollbackSetting","Rollback on All Devices");
		   	 data.put("configDeliveryTaskDeliveryOrderSetting","parallel");
		   	 JsonObject configTemplateRef = new JsonObject();
		   	 JsonArray paramValues = new JsonArray();
		   	 paramValues.add(Interface);
  		     paramValues.add(ACLname);
  		    
		   	 if (Protocol == null) {
		   		templatename = templatename + "_removal";
		   	 } else {
		   		 paramValues.add(SRCIP);
	    		 paramValues.add(DSTIP);
	    		 paramValues.add(SRCMask);
	    		 paramValues.add(DSTMask);
	    		 paramValues.add(Action);
	    		 paramValues.add(Protocol);
		   		 if (Port != null) {
		   			 templatename = templatename + "_port";
		   			 paramValues.add(Port);
		   		 } else {
		   			 templatename = templatename + "_no_port";
		   		 }
		   	 }
		   	 configTemplateRef.put("name",templatename);
		   	 data.put("configTemplateRef",configTemplateRef);
    		 
    		 JsonObject parameter = new JsonObject();
    		 // n7k address
//    		 parameter.put("ipAddress","12.1.1.2");
    		 //this is the address of the switch that the template will be pushed
    		 // n5k
    		 parameter.put("ipAddress","172.27.252.43");
		   	 parameter.put("paramValues", paramValues);
		   	 
		   	 JsonArray configDeliveryTaskDeviceDetailsCol = new JsonArray();
		   	 configDeliveryTaskDeviceDetailsCol.add(parameter);
		   	 data.put("configDeliveryTaskDeviceDetailsCol",configDeliveryTaskDeviceDetailsCol);
		   	 data.put("isCopyRunToStartTask","false");
		   	 // credentials for the switch login
		   	 data.put("userName","admin");
		   	 data.put("password","cisco123");
		     
   		
		     System.out.println("DCNM logon " + header);
		     System.out.println("DCNM profile " + data);
	         DCNM_Send(HttpMethod.POST, "/fmrest/config/templates/jobs", header, data.toString(), dcnmresp -> {
		             if (dcnmresp.success && dcnmresp.body != null) {
		                 System.out.println("Schedule job suceeded " + dcnmresp.body.toString());		                 
		             }
		             else {
		                 System.out.println("Schedule Error " + dcnmresp.toString()); 
		             }
		        });
	    }
}
