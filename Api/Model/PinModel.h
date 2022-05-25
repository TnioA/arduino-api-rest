#ifndef _PINMODEL_H
#define _PINMODEL_H

#include <SPI.h>

class PinModel {
    public: 
        int Code;
        String Type;
        String SubType;
        float Value;

        PinModel(int code, String type, String subType, float value);
        String ToJson();
};

#endif