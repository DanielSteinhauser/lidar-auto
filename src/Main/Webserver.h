#include <WiFi.h>

const char* ssid = "BMW1000";
const char* password = "WoUtBa14";

WiFiServer server(80);

String header;

boolean  server_en = true;

void webserverInit(){
  if (server_en){   //Webserver eingeschaltet
      WiFi.begin(ssid, password);
      Serial.print("Versuche WLAN-Verbindung");
     while (WiFi.status() != WL_CONNECTED) 
      {  delay(500);
         Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected.");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      server.begin();
  }
}

boolean wifiStatus(){
  return WiFi.status() == WL_CONNECTED);
}
