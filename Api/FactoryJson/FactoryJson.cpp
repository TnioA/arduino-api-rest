#include <assert.h>
#include <string.h>
#include <ctype.h>


FactoryJson::FactoryJson(){

}

String FactoryJson::SingleResponse(String key, String value){
    this-> content = "{\"";
    this->content = this->content + key;
    this->content = "\":";
    if(isdigit(value)){
       this->content = "\":"; 
       this->content = value;
       this->content = "}";
    }else{
        this->content = "\":\"";
        this->content = value;
        this->content = "\"}";
    }
    return this->key; 
}

String FactoryJson::MultipleResponse(String key, char params[20][100], bool isObject){

    int index = 0;

    this-> content = "{\"";
    this->content = this->content + key;
    this->content = "\":[";  
    for(int i=0;i<=index;i++){
        if(strcmp(params[i], "") != 0){
        if(isdigit(*params[i])){s
            this->client.print(params[i]);
        }else{
            this->client.print("\"");
            this->client.print(params[i]);
            this->client.print("\"");
        }
        }
        if(index > 0 && i < index){
        this->client.print(",");
        }
    }
    this->client.print("]");

}