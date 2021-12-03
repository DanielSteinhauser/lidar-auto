#include "Lidar.h"
#include "Display.h"
#include "Steuerung.h"
#include "Webserver.h"
 bool server_en = true;

void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  
  stepper.setSpeed(5);
  
  if (server_en){   //Webserver eingeschaltet
      WiFi.begin(ssid, password);
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
  
  displayInit();
  motorInit();
}



void loop() {
  scanStepper(15);
  displayDatenSchreiben();
  
  if(kurz){
    int n = 0;
    
    scanStepper(45);
    kurz = false;
  }
 
}
