#ifndef _ROUTER_H
#define _ROUTER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class Router {
    private:
        EthernetClient _client;

    public: 
        Router();
        String * RouteRequest(String method, String request);
        String GetParam(String url, String param);
	    bool StartsWith(const char*, const char*);
};

#endif