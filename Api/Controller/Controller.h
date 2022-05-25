#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <DataResponse.h>
#include <PinModel.h>
#include <DHT.h>

class Controller {
    public: 
        Controller();
        DataResponse SetPinType(int pin, String type);

        DataResponse SetDigitalPin(int pin, bool value);
        DataResponse SetAnalogPin(int pin, int value);

        DataResponse GetDigitalPin(int pin);
        DataResponse GetAnalogPin(int pin);
        DataResponse GetVirtualPin(int pin);

    private:
        int GetPinMode(uint8_t pin);
};

#endif