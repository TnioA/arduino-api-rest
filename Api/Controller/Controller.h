#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class Controller {
    private:
        EthernetClient client;

    public: 
        Controller(EthernetClient external_client);
        void ReturnInfo(String url, char params[10][100], int index);
        void ReturnValues();
        void SetDigitalPin(int pin, bool value);
        void SetAnalogPin(int pin, int value);
        void GetDigitalPin(int pin);
        void GetAnalogPin(int pin);
        void ErrorMessage();
};

#endif