package com.cisco.crossdomain.cdpe.test;

import io.vertx.core.Vertx;
import io.vertx.ext.unit.Async;
import io.vertx.ext.unit.TestContext;
import java.util.logging.Logger;
import java.util.logging.Level; 

import com.cisco.crossdomain.cdpe.DomainControllerPlugin;
import com.cisco.crossdomain.cdpe.NBAPIService;
import com.cisco.crossdomain.cdpe.PolicyDistributor;

public class TestCommon {

	String domainVerticleID = null;
	String policyVerticleID = null;
	String NBAPIVerticleID = null;
	final String servicePropertiesFile = "config/JUnitNBAPI.properties"; 
	private Vertx myVertx; 
	int undeploymentCounter = 0; 
	
	final static Logger LOGGER = Logger.getLogger(TestCommon.class.getName()); 
	
	TestCommon() { 
		LOGGER.setLevel(Level.WARNING); 
	}
	
	void increaseUndeploymentCounter() { 		
		undeploymentCounter++; 
	}
	
	Vertx getMyVertx() { 
		return myVertx; 
	}
	
	void setUndeploymentCounter(int counter) { 
		undeploymentCounter = counter; 
	}
	
	public void initCDPEService(TestContext context, Vertx vertx, int port, 
								Async async)
			throws InterruptedException {
	
		vertx.deployVerticle(new DomainControllerPlugin(), res1 -> {
			if (res1.succeeded()) {
				domainVerticleID = res1.result();
				LOGGER.info("Deployment id domainVerticleID is: " + domainVerticleID);
				vertx.deployVerticle(new PolicyDistributor(),  res2-> {
					if (res2.succeeded()) {
						policyVerticleID = res2.result();
						LOGGER.info("Deployment id policyVerticleID is: "
								+ res2.result());						
						vertx.deployVerticle(
								new NBAPIService(port, servicePropertiesFile),
								  res3 -> {
									if (res3.succeeded()) {
										NBAPIVerticleID = res3.result();
										LOGGER.info("Deployment id NBAPIVerticleID is: "
												+ NBAPIVerticleID);
										 
									} else {
										LOGGER.severe("Deployment failed!");
										context.fail(res3.cause());
									}
									async.complete();					
								});

					} else {
						LOGGER.severe("Deployment failed!");
						context.fail(res2.cause());
						async.complete();
					}
					
				});
			
			} else {
				LOGGER.severe("Deployment failed!");
				context.fail(res1.cause());
				async.complete();
			}
		});

		// change to use conditional logger
		LOGGER.info("Deployed all verticles successfully");
		
		for (String s : vertx.deploymentIDs()) {
			// use conditional logger instead later 
			LOGGER.info("the deployed string are " + s);
		}

	}

	public void startVerticles(TestContext context, int port) throws InterruptedException {
		myVertx = Vertx.vertx();
		Async async = context.async();
		initCDPEService(context, myVertx, port, async);		
	}

	public void closeVerticles(TestContext context) throws InterruptedException {
		Async async = context.async();
		finiCDPEService(context, myVertx, async); 
		myVertx.close(context.asyncAssertSuccess());
	}
	
	public void finiCDPEService(TestContext context, Vertx vertx, Async async) 
			throws InterruptedException {
		
		setUndeploymentCounter(0); 
		LOGGER.info(" getting into undeployment"); 
		
		/*
		 * undelopy all verticles in deployment vertex
		 */
		for (String deployID : vertx.deploymentIDs()) {
			LOGGER.info("the deployed strings are " + deployID);

			vertx.undeploy(deployID, res -> {
				increaseUndeploymentCounter(); 
				if (res.succeeded()) {
					LOGGER.info("Undeployed ok" + deployID);
				} else {
					LOGGER.severe("Undeploy failed!");
				}
			});	
		}
		
		
		while (undeploymentCounter < 3) { 
			Thread.sleep(10); 	
		}
		async.complete(); 
	}
	
}
