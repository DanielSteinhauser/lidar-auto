#include <WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORT";

WiFiServer server(80);

String header;

void webserverInit(){
      WiFi.begin(ssid, password);
      Serial.print("Versuche WLAN-Verbindung");
      aufDisplayAnzeigen(0, 0, "Versuche Wlan verbindung");
     while (WiFi.status() != WL_CONNECTED) 
      {  delay(500);
         Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      aufDisplayAnzeigen(0, 20, "Erfolg");
      delay(1000);
      server.begin();
}

boolean wifiStatus(){
  return WiFi.status() == WL_CONNECTED;
}


void webserverClientUeberpruefen() {
    WiFiClient client = server.available(); // Listen for incoming clients
    
    if (client){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        
        // Display the HTML web page
        client.println("<!DOCTYPE html><html>");
        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
        client.println("</head><body><h1>ESP32 Webserver</h1>");        
        client.println("</body></html>"); 
        
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
