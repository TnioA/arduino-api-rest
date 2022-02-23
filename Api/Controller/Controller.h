#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

class Controller {
    public: 
        Controller();
        String * SetDigitalPin(int pin, bool value);
        String * SetAnalogPin(int pin, int value);
        String * GetDigitalPin(int pin);
        String * GetAnalogPin(int pin);
};

#endif