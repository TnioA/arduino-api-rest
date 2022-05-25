#include <SPI.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <PinModel.h>

PinModel::PinModel(int code, String type, String subType, float value){
    Code = code;
    Type = type;
    SubType = subType;
    Value = value;
}

String PinModel::ToJson(){
    String response = "";

    response += "{\"code\":\"" + SubType;
    response += Code;
    response += "\",";
    response += "\"type\":\"Output\"";
    response += ",";
    response += "\"value\":";
    response += Value;
    response += "}";
    
    return response; 
}