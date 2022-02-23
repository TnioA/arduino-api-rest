#include <SPI.h>
#include <Ethernet.h>
#include <Proccessor.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 0, 15);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
    EthernetClient client = server.available();
    Proccessor proccessor = Proccessor(client);
    proccessor.ProccessRequest();
}