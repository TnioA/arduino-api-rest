#ifndef _ROUTER_H
#define _ROUTER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class Router {
    private:
        EthernetClient client;
        String url;

    public: 
        Router(EthernetClient external_client, String external_url);
        void RoutingUrl();
};

#endif