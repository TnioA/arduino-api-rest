#ifndef _ROUTER_H
#define _ROUTER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DataResponse.h>

class Router {
    public: 
        EthernetClient _client;

        Router();
        DataResponse RouteRequest(String method, String request);   

    private:
        String GetParam(String url, String param);
	    bool StartsWith(const char*, const char*);    
};

#endif