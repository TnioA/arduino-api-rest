void ReturnValues(EthernetClient client){
  temperature = myTMP36.getTempC();
  client.print("{\"light-level\":");
  client.print(lightlevel);
  client.print(",\"temperature\":");
  client.print(temperature);
  client.print(",\"door-state\":");
  client.print(digitalRead(8) == 0 ? "false" : "true");
  client.print("}");  
}

void SetDigitalPin(EthernetClient client, int pin, bool value){
  pinMode(pin, OUTPUT);
  if(pin == 9){
    lightlevel = value;
  }
  digitalWrite(pin,value);
  client.print("{\"pin\":");
  client.print(pin);
  client.print(",\"value\":");
  client.print(value);
  client.print("}");
}

void SetAnalogPin(EthernetClient client, int pin, int value){
  pinMode(pin, OUTPUT);
  if(pin == 9){
    lightlevel = value;
  }
  analogWrite(pin,value);
  client.print("{\"pin\":");
  client.print(pin);
  client.print(",\"value\":");
  client.print(value);
  client.print("}");
}

void GetPin(EthernetClient client, int pin){
  client.print("{\"value of pin\":");
  client.print(pin);
  client.print("}");
}

void ErrorMessage(EthernetClient client){
  client.print("{\"Erro\":\"Err: Url not finded\"");
  client.print("}");  
}
