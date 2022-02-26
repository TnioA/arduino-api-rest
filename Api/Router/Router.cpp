#include <Router.h>
#include <FactoryJson.h>
#include <Controller.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Controller.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

Router::Router(){}

String * Router::RouteRequest(String method, String request) {
    static String response[2];
    if(!StartsWith(request.c_str(), "/api/")){
        return FactoryJson().ErrorResponse("Not finded an route that satisfyes this request.");
    }

    if(strstr(request.c_str(), "setpintype") != NULL){
        int pin = atoi(GetParam(request, "pin").c_str());
        String type = GetParam(request, "type");
        return Controller().SetPinType(pin, type);
    }
    if(strstr(request.c_str(), "getdigitalpin") != NULL){
        int pin = atoi(GetParam(request, "pin").c_str());
        return Controller().GetDigitalPin(pin);
    }
    else if(strstr(request.c_str(), "getanalogpin") != NULL){
        int pin = atoi(GetParam(request, "pin").c_str());
        return Controller().GetAnalogPin(pin);
    }
    else if(strstr(request.c_str(), "setdigitalpin") != NULL){
        int pin = atoi(GetParam(request, "pin").c_str());
        int value = atoi(GetParam(request, "value").c_str());
        return Controller().SetDigitalPin(pin, value);
    }
    else if(strstr(request.c_str(), "setanalogpin") != NULL){
        int pin = atoi(GetParam(request, "pin").c_str());
        int value = atoi(GetParam(request, "value").c_str());
        return Controller().SetAnalogPin(pin, value);
    }
    else{
        return FactoryJson().ErrorResponse("Not finded an route that satisfies this request.");
    }
}

bool Router::StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

String Router::GetParam(String url, String paramName){
    static String response[10];
    String aux = "";
    bool foundParam = 0;

    char char_array[url.length() + 1];
    strcpy(char_array, url.c_str());
    char *token = strtok(char_array, "?");
    int count = 0;
    while (token != NULL)
    {
        if(count > 0){
            aux = token;
            break;
        }
        token = strtok(NULL, "?");

        count++;
    }

    char_array[aux.length() + 1];
    strcpy(char_array, aux.c_str());
    char *token2 = strtok(char_array, "&");
    aux = "";
    while (token2 != NULL)
    {
        if(StartsWith(token2, (paramName+"=").c_str())){
            aux = token2;
            aux.remove(0, paramName.length()+1);
            break;
        }

        token2 = strtok(NULL, "&");
    }

    return aux;
}