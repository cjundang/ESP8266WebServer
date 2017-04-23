#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "UbiNES";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot(){
  server.send(200, "text/plain", "Hello");
  }

void handleArgs(){
  String message = "#argument: ";
  message += server.args();
  message += "<br/>";
  for(uint8_t i = 0; i < server.args(); i++){
    message += " " + server.argName(i) + " : ";
    message += " " + server.arg(i) + "<br/>";
    }
    Serial.println(message);
    server.send(200, "text/html", message);
  }

  void handleNotFound(){
    String message = "File not found";
    server.send(404, "text/plain", message);
    }
    
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/args", handleArgs);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();

}
