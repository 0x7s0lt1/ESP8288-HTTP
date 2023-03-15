#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>


int PORT = 80;

const char* ssid = "...";
const char* pswd = "...";

ESP8266WebServer server(PORT);

void setup() {
  
  Serial.begin(9600);
  delay(100);
  while(!Serial) continue;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pswd);
  Serial.println("Connecting..");

  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Wifi Connected!");
  Serial.print("Got IP:");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started!");

}

void loop() {
  
  server.handleClient();

}


void handle_OnConnect() {
  server.send(200, "application/json", "{'status':200}");
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

  