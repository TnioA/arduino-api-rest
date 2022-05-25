#include <SPI.h>
#include <Controller.h>
#include <DataResponse.h>
#include <PinModel.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);


Controller::Controller(){
  dht.begin();
}

// route: /api/setpintype/
DataResponse Controller::SetPinType(int pin, String type){
  if(type == "input") pinMode(pin, INPUT);
  else if(type == "output") pinMode(pin, OUTPUT);
  else if(type == "input_pullup") pinMode(pin, INPUT_PULLUP);
  else return DataResponse().ErrorResponse("Are only valid values input, output or input_pullup as a pin type.");

  return DataResponse().SuccessData();
}

// route: /api/setdigitalpin/
DataResponse Controller::SetDigitalPin(int pin, bool value){
  if(GetPinMode(pin) != OUTPUT)
    return DataResponse().ErrorResponse("This pin is not setted as OUTPUT. Do that first.");

  digitalWrite(pin, value);
  return DataResponse().SuccessData(PinModel(pin, "output", "D", value).ToJson());
}

// route: /api/setanalogpin/
DataResponse Controller::SetAnalogPin(int pin, int value){
  if(value < 0 || value > 255){
    return DataResponse().ErrorResponse("Are only valid values between 0 and 255 for analog write.");
  }

  if(GetPinMode(pin) != OUTPUT)
    return DataResponse().ErrorResponse("This pin is not setted as OUTPUT. Do that first.");

  analogWrite(pin,value);
  return DataResponse().SuccessData(PinModel(pin, "output", "A", value).ToJson());
}

// route: /api/getdigitalpin/
DataResponse Controller::GetDigitalPin(int pin){
  if(GetPinMode(pin) != INPUT)
    return DataResponse().ErrorResponse("This pin is not setted as INPUT or INPUT_PULLUP. Do that first.");

  return DataResponse().SuccessData(PinModel(pin, "input", "D", digitalRead(pin)).ToJson());
}

// route: /api/getanalogpin/
DataResponse Controller::GetAnalogPin(int pin){
  if(GetPinMode(pin) != INPUT)
    return DataResponse().ErrorResponse("This pin is not setted as INPUT or INPUT_PULLUP. Do that first.");

  return DataResponse().SuccessData(PinModel(pin, "input", "A", analogRead(pin)).ToJson());
}

// route: /api/getvirtualpin/
DataResponse Controller::GetVirtualPin(int pin){
  switch (pin){
    case 150:
      delay(2000);
      return DataResponse().SuccessData(PinModel(pin, "output", "V", dht.readTemperature() - 3).ToJson());
      break;
    case 151:
      delay(2000);
      return DataResponse().SuccessData(PinModel(pin, "output", "V", dht.readHumidity() + 3).ToJson());
      break;
    default:
      return DataResponse().ErrorResponse("Any value was founded for this pin.");
      break;
  }
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