package com.cisco.crossdomain.cdpe;

import io.vertx.core.Vertx;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        Vertx vertx = Vertx.vertx();

        vertx.deployVerticle(new DomainControllerPlugin()) ;
        vertx.deployVerticle(new PolicyDistributor()) ;
        
        Thread.sleep(300);
        vertx.deployVerticle(new NBAPIService()) ;
        
        System.out.println("Deployed verticles") ;
    }

}