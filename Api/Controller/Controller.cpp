#include <SPI.h>
#include <Controller.h>
#include <Ethernet.h>
#include <TMP36.h>

TMP36 myTMP36(A0, 5.0);
int temperature = 0;
bool doorstate = false;
int lightlevel = 0;

Controller::Controller(EthernetClient ethernetClient){
  this->client = ethernetClient;
}

// route: /
void Controller::ReturnInfo(String url, char params[10][100], int index){
  String strsp = "\""; // VARIABLE USED TO ADD "" AT ATTR WITH STRING TYPE

  this->client.print("{\"parameters\": {\"status\": 1,\"Number\":");
  this->client.print(index > 0 ? index : 0);
  this->client.print(",\"full-route\": \"");
  this->client.print(url);
  this->client.print("\"}, \"atributes\":[");  
  for(int i=0;i<=index;i++){
    if(strcmp(params[i], "") != 0){
      if(isdigit(*params[i])){
        this->client.print(params[i]);
      }else{
        this->client.print(strsp);
        this->client.print(params[i]);
        this->client.print(strsp);
      }
    }
    if(index > 0 && i < index){
      this->client.print(",");
    }
  }
  this->client.print("],\"response\":");
} 

// route: /
void Controller::ReturnValues(){
  this->client.print("{\"light-level\":");
  this->client.print(lightlevel);
  this->client.print(",\"temperature\":");
  this->client.print(myTMP36.getTempC());
  this->client.print(",\"door-state\":");
  this->client.print(digitalRead(8) == 0 ? "false" : "true");
  this->client.print("}");  
}

// route: /api/setpin/
void Controller::SetDigitalPin(int pin, bool value){
  pinMode(pin, OUTPUT);
  if(pin == 9){
    lightlevel = value;
  }
  digitalWrite(pin,value);
  this->client.print("{\"pin\":");
  this->client.print(pin);
  this->client.print(",\"value\":");
  this->client.print(value);
  this->client.print("}");
}

// route: /api/setpin/
void Controller::SetAnalogPin(int pin, int value){
  pinMode(pin, OUTPUT);
  if(pin == 9){
    lightlevel = value;
  }
  analogWrite(pin,value);
  this->client.print("{\"pin\":");
  this->client.print(pin);
  this->client.print(",\"value\":");
  this->client.print(value);
  this->client.print("}");
}

// route: /api/getdigitalpin/
void Controller::GetDigitalPin(int pin){
  pinMode(pin, INPUT);
  this->client.print("{\"pin\":");
  this->client.print(pin);
  this->client.print(",\"value\":");
  this->client.print(digitalRead(pin));
  this->client.print("}");
}

// route: /api/getanalogpin/
void Controller::GetAnalogPin(int pin){
  pinMode(pin, INPUT);
  this->client.print("{\"pin\": \"A");
  this->client.print(pin);
  this->client.print("\"");
  this->client.print(",\"value\":");
  this->client.print(analogRead(pin));
  this->client.print("}");
}

// route: error
void Controller::ErrorMessage(){
  this->client.print("{\"Erro\":\"Err: Url not finded\"");
  this->client.print("}");  
}
