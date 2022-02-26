#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class Controller {
    public: 
        Controller();
        String * SetPinType(int pin, String type);
        String * SetDigitalPin(int pin, bool value);
        String * SetAnalogPin(int pin, int value);
        String * GetDigitalPin(int pin);
        String * GetAnalogPin(int pin);

    private:
        int GetPinMode(uint8_t pin);
};

#endif