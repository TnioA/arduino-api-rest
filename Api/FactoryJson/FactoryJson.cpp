#include <FactoryJson.h>
#include <SPI.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

FactoryJson::FactoryJson(){}

String * FactoryJson::ErrorResponse(String message){
    static String response[2];

    response[0] = "400";
    response[1] = "{\"error\":\""+ message +"\",\"success\":\"false\"}";
    return response; 
}

String * FactoryJson::PinSettedResponse(int pin, String type){
    static String response[2];

    response[0] = "200";
    response[1] = "";
    response[1] += "{\"pin\":";
    response[1] += "{\"code\":\"";
    response[1] += pin;
    response[1] += "\",";
    response[1] += "\"type\":\"" + type + "\"";
    response[1] += "},";
    response[1] += "\"success\":\"true\"}";
    
    return response; 
}

String * FactoryJson::DigitalPinResponse(int pin, String type, bool value){
    static String response[2];
    String trueValue = value ? "true" : "false";

    response[0] = "200";
    response[1] = "";
    response[1] += "{\"pin\":";
    response[1] += "{\"code\":\"D";
    response[1] += pin;
    response[1] += "\",";
    response[1] += "\"type\":\"" + type + "\"";
    response[1] += ",";
    response[1] += "\"value\":\"" +  trueValue + "\"";
    response[1] += "},";
    response[1] += "\"success\":\"true\"}";
    
    return response; 
}

String * FactoryJson::AnalogPinResponse(int pin, String type, int value){
    static String response[2];

    response[0] = "200";
    response[1] = "";
    response[1] += "{\"pin\":";
    response[1] += "{\"code\":\"A";
    response[1] += pin;
    response[1] += "\",";
    response[1] += "\"type\":\"" + type + "\"";
    response[1] += ",";
    response[1] += "\"value\":";
    response[1] += value;
    response[1] += "},";
    response[1] += "\"success\":\"true\"}";

    return response; 
}