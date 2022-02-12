#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "hrsiot";
const char* password = "12345678";

const char* server = "test.mosquitto.org";  // Adresse des MQTT-Brokers im Netz

const char* topicPublish = "gswt/herbert";    // Topic unter dem die Demo-Daten publiziert werden sollen
const char* topicSubscribe = "gswt/herbert";    // Topic unter dem die Demo-Daten publiziert werden sollen

WiFiClient wifiClient;
PubSubClient client(server, 1883, wifiClient);

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
      
      if (client.connect("Herbert")) {
      Serial.println("Connected to MQTT-Broker");
      }
    
      delay(1000);
}
