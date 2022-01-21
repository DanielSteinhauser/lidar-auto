<<<<<<< Updated upstream
=======
boolean  server_en = false; // Webserver Hauptschalter

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
  
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
=======
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  displayInit();
  if (server_en) webserverInit();
  geradeausfahren();
>>>>>>> Stashed changes
}



void loop() {
  scanStepper(15);
  displayDatenSchreiben();
  
  if(kurz){
    scanStepper(45);
    kurz = false;
  }
 
}
