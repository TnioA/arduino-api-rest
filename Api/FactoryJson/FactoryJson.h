#ifndef _FACTORYJSON_H
#define _FACTORYJSON_H

#include <SPI.h>

class FactoryJson {
    public: 
        FactoryJson();
        String * ErrorResponse(String message);
        String * DigitalPinResponse(int pin, String type, bool value);
        String * AnalogPinResponse(int pin, String type, int value);
};

#endif