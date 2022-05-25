#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Router.h>
#include <DataResponse.h>

class Processor {
    public: 
        EthernetClient _client;
        Router _router;
        String _request;

        Processor(EthernetClient externalClient);
        void ProcessRequest();      

    private:
        String GetMethod(String fullRequest);
        String GetUrl(String fullRequest);
        void SetHeaders(EthernetClient client, int statusCode); 
};

#endif