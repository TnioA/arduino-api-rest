#include <SPI.h>
#include <Controller.h>
#include <FactoryJson.h>
#include <Ethernet.h>
//#include <TMP36.h>

//TMP36 myTMP36(A0, 5.0);
int temperature = 0;
bool doorstate = false;
int lightlevel = 0;

Controller::Controller(){
}

// route: /api/setdigitalpin/
String * Controller::SetDigitalPin(int pin, bool value){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
  return FactoryJson().DigitalPinResponse(pin, "output", value);
}

// route: /api/setanalogpin/
String * Controller::SetAnalogPin(int pin, int value){
  if(value < 0 || value > 255){
    return FactoryJson().ErrorResponse("Are only valid values between 0 and 255 for analog write.");
  }

  pinMode(pin, OUTPUT);
  analogWrite(pin,value);
  return FactoryJson().AnalogPinResponse(pin, "output", value);
}

// route: /api/getdigitalpin/
String * Controller::GetDigitalPin(int pin){
  pinMode(pin, INPUT);
  return FactoryJson().DigitalPinResponse(pin, "input", digitalRead(pin));
}

// route: /api/getanalogpin/
String * Controller::GetAnalogPin(int pin){
  pinMode(pin, INPUT);
  return FactoryJson().AnalogPinResponse(pin, "input", analogRead(pin));
}