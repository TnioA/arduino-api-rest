#include <SPI.h>
#include <Controller.h>
#include <FactoryJson.h>
#include <Ethernet.h>

Controller::Controller(){}

// route: /api/setpintype/
String * Controller::SetPinType(int pin, String type){
  if(type == "input") pinMode(pin, INPUT);
  else if(type == "output") pinMode(pin, OUTPUT);
  else if(type == "input_pullup") pinMode(pin, INPUT_PULLUP);
  else return FactoryJson().ErrorResponse("Are only valid values input, output or input_pullup as a pin type.");

  return FactoryJson().PinSettedResponse(pin, type);
}

// route: /api/setdigitalpin/
String * Controller::SetDigitalPin(int pin, bool value){
  if(getPinMode(pin) != OUTPUT)
    return FactoryJson().ErrorResponse("This pin is not setted as OUTPUT. Do that first.");


  digitalWrite(pin, value);
  return FactoryJson().DigitalPinResponse(pin, "output", value);
}

// route: /api/setanalogpin/
String * Controller::SetAnalogPin(int pin, int value){
  if(value < 0 || value > 255){
    return FactoryJson().ErrorResponse("Are only valid values between 0 and 255 for analog write.");
  }

  if(getPinMode(pin) != OUTPUT)
    return FactoryJson().ErrorResponse("This pin is not setted as OUTPUT. Do that first.");

  analogWrite(pin,value);
  return FactoryJson().AnalogPinResponse(pin, "output", value);
}

// route: /api/getdigitalpin/
String * Controller::GetDigitalPin(int pin){
  if(getPinMode(pin) != INPUT)
    return FactoryJson().ErrorResponse("This pin is not setted as INPUT or INPUT_PULLUP. Do that first.");

  return FactoryJson().DigitalPinResponse(pin, "input", digitalRead(pin));
}

// route: /api/getanalogpin/
String * Controller::GetAnalogPin(int pin){
  if(getPinMode(pin) != INPUT)
    return FactoryJson().ErrorResponse("This pin is not setted as INPUT or INPUT_PULLUP. Do that first.");

  return FactoryJson().AnalogPinResponse(pin, "input", analogRead(pin));
}

int Controller::GetPinMode(uint8_t pin){
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  volatile uint8_t *reg, *out;

  if(port == NOT_A_PIN) return -1;

  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if((~*reg & bit) == bit){
    if((~*out & bit)  == bit) return INPUT;
    else return INPUT_PULLUP;
  }

  return OUTPUT;
}