#include <SPI.h>
#include <Ethernet.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <TMP36.h>

// Temperature Sensor
TMP36 myTMP36(A0, 5.0);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 100, 250);
EthernetServer server(80);

int temperature = 0;
bool doorstate = false;
int lightlevel = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  temperature = myTMP36.getTempC();
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String url;
    int aux = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        //SESSION FOR GETTING ROUTES
        if(url.length() < 100){
          if(c == '/' && aux == 0){
            aux = aux + 1;
          }
          if(aux == 1){
            url += c;
          }
          if(c == ' ' && aux == 1){
            aux = 2;
          }
        }
        
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Access-Control-Allow-Origin: *");
          //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          ControllerApi(client, url);
          // output the value of each analog input pin
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void ControllerApi(EthernetClient client, String url){
  char params[10][100] = {"","","","","","","","","",""};
  int index = 0;
  String aux = "";
  String strsp = "\"";
  char* conc;
  
  //SESSION FOR GETTING ROUTES
  if(url.length() > 2){
    for(int i = 0; i < url.length()-1; i++){
      if(url[i] == '/'){
        aux = "";
        index++;
      }else{
        aux = url[i];
        char* foo = aux.c_str();
        strcat(params[index], foo);
      }
    }
  }

  client.print("{\"parameters\": {\"status\": 1,\"Number\":");
  client.print(index > 0 ? index : 0);
  client.print(",\"full-route\": \"");
  client.print(url);
  client.print("\"}, \"atributes\":[");  
  for(int i=1;i<=index;i++){
    if(strcmp(params[i], "") != 0){
      if(isdigit(*params[i])){
        client.print(params[i]);
      }else{
        //conc = "";
        //conc = strsp.c_str();
        //client.println(strcat(conc, strcat(params[i],conc)));
        client.print(strsp);
        client.print(params[i]);
        client.print(strsp);
      }
    }
    if(index > 0 && i < index){
      client.print(",");
    }
  }

  //GETTING CONTENT RETURN
  client.print("],\"response\":");

  //MAPPING ROUTES CONTENT
  if(strcmp(params[1], "") == 0){
    ReturnValues(client);   
  }
  else if(strcmp(params[1], "api") == 0){
    if(strcmp(params[2], "setpin") == 0){
      if(isdigit(*params[3])){
        if((strcmp(params[4], "true") == 0) || (strcmp(params[4], "false") == 0)){
          SetDigitalPin(client, atoi(params[3]), (strcmp(params[4], "true") == 0) ? true : false);
        }else{
          if(isdigit(*params[4])){
            SetAnalogPin(client, atoi(params[3]), atoi(params[4]));
          }else{
            ErrorMessage(client);
          }
        }
      }else{
        ErrorMessage(client);
      }
    }
    else if(strcmp(params[2], "getpin") == 0){
      if(isdigit(*params[3])){
        GetPin(client, atoi(params[3]));
      }else{
        ErrorMessage(client);
      }
    }
    else{
      ErrorMessage(client);
    }
  }
  else{
    ErrorMessage(client);
  }
  client.print("}");
  
}


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
