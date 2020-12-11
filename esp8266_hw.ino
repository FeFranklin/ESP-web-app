#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);  // Create server with port 80
const char* ssid = "your network";  // Name of network
const char* password = "your password";  //Password of local network
int LED = 5;  // Set GPIO pin as LED to facilitate code afterwards

void setCrossOrigin() {
  server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
  server.sendHeader(F("Access-Control-Max-Age"), F("600"));
  server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
  server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

void handle_connect() {
  Serial.println("Testing connection.");
  setCrossOrigin();
  if(wifiMulti.run() == WL_CONNECTED){
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    server.send(200, "text/plain", "ESP is connected");
  }
  
}

void handle_on() {
  Serial.println("Turned LED on.");
  setCrossOrigin();
  digitalWrite(LED, HIGH);
  server.send(200, "text/plain", "Led is now HIGH");
}

void handle_off() {
  Serial.println("Turned LED off.");
  setCrossOrigin();
  digitalWrite(LED, LOW);
  server.send(200, "text/plain", "Led is now LOW");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED, OUTPUT);           // Set the GPIO port 5 as an output

  Serial.begin(115200);
  // Connetec to WiFi
  wifiMulti.addAP(ssid, password); // Wifi connection with name of network and password
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');   // Print in serial monitor response of the connection to the esp
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  server.on("/on", handle_on);
  server.on("/off", handle_off);
  server.on("/connect", handle_connect);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
