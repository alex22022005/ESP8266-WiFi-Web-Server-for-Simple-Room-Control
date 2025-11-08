#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define led D4

const char* ssid = "Mr.lonely"; // Your WiFi network SSID
const char* password = "antony...."; // Your WiFi network password

ESP8266WebServer server(80); // Create a web server object that listens on port 80

bool lightState = false; // Variable to store the state of the light
bool fanState = false; // Variable to store the state of the fan

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Route handlers
  server.on("/", HTTP_GET, handleRoot);
  server.on("/light", HTTP_GET, handleLight);
  server.on("/fan", HTTP_GET, handleFan);
  
  // Start server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient(); // Handle client requests
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Room Control</title></head><body>";
  html += "<h1>Room Control</h1>";
  html += "<h2>Light</h2>";
  html += "<form action=\"/light\" method=\"get\">";
  html += "<button type=\"submit\">";
  html += lightState ? "Turn Off" : "Turn On";
  html += "</button>";
  html += "</form>";
  html += "<h2>Fan</h2>";
  html += "<form action=\"/fan\" method=\"get\">";
  html += "<button type=\"submit\">";
  html += fanState ? "Turn Off" : "Turn On";
  html += "</button>";
  html += "</form>";
  html += "</body></html>";
  
  server.send(200, "text/html", html); // Send the HTML page to the client
}

void handleLight() {
  lightState = !lightState; // Toggle the state of the light
  digitalWrite(led, lightState ? HIGH : LOW); // Control the LED (assumed to be connected to built-in LED pin)
  handleRoot(); // Redirect to the main page
}

void handleFan() {
  fanState = !fanState; // Toggle the state of the fan
  // Code to control the fan can be added here
  handleRoot(); // Redirect to the main page
}
