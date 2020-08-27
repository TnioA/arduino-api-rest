#include <Router.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Controller.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

Router::Router(EthernetClient external_client, String external_url){
    this->client = external_client;
    this->url = external_url;
}

void Router::RoutingUrl() {
    Controller controller(this->client);

    char params[10][100] = {"","","","","","","","","",""};
    int index = 0;
    String aux = "";
    char* conc;

    // IF THERE IS A " " AT THE END, IT'S REMOVED
    if(this->url[this->url.length()-1] == ' '){
        this->url.remove(this->url.length()-1, 1);
    }

    // IF THERE IS A "/" AT THE END, IT'S REMOVED
    while(this->url[this->url.length()-1] == '/'){
        this->url.remove(this->url.length()-1, 1);
    }
    
    //SESSION FOR GETTING PARAMS
    if(this->url.length() > 2){
        for(int i = 0; i < this->url.length(); i++){
        if(this->url[i] == '/'){
            aux = "";
            if(i > 0){
            index++;   
            }
        }else{
            aux = this->url[i];
            char* foo = aux.c_str();
            strcat(params[index], foo);
        }
        }
    }

    // PRINCIPAL RETURN
    controller.ReturnInfo(this->url, params, index);

    //MAPPING ROUTES CONTENT
    if(strcmp(params[0], "") == 0){
        controller.ReturnValues();   
    }
    else if(strcmp(params[0], "api") == 0){
        if(strcmp(params[1], "setpin") == 0){
            if(isdigit(*params[2])){
                if((strcmp(params[3], "true") == 0) || (strcmp(params[3], "false") == 0)){
                        controller.SetDigitalPin(atoi(params[2]), (strcmp(params[3], "true") == 0) ? true : false);
                }else{
                    if(isdigit(*params[3])){
                        controller.SetAnalogPin(atoi(params[2]), atoi(params[3]));
                    }else{
                        controller.ErrorMessage();
                    }
                }
            }else{
                controller.ErrorMessage();
            }
        }
        else if(strcmp(params[1], "getdigitalpin") == 0){
            if(isdigit(*params[2])){
                controller.GetDigitalPin(atoi(params[2]));
            }else{
                controller.ErrorMessage();
            }
        }
        else if(strcmp(params[1], "getanalogpin") == 0){
            if(isdigit(*params[2])){
                controller.GetAnalogPin(atoi(params[2]));
            }else{
                controller.ErrorMessage();
            }
        }
        else{
            controller.ErrorMessage();
        }
    }
    else{
        controller.ErrorMessage();
    }

    // ENDING RETURN
    client.print("}");
    
}