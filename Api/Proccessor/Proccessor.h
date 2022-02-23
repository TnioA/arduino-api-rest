#ifndef _PROCCESSOR_H
#define _PROCCESSOR_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Router.h>

class Proccessor {
    private:
        EthernetClient _client;
        Router _router;
        String _request;

    public: 
        Proccessor(EthernetClient externalClient);
        void ProccessRequest();
        String GetMethod(String fullRequest);
        String GetUrl(String fullRequest);
        void SetHeaders(EthernetClient client, int statusCode);
};

#endif