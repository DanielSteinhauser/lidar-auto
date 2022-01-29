boolean  server_en = false; // Webserver Hauptschalter

#include "Lidar.h"
#include "Display.h"
#include "Webserver.h"        // Reihenfolge hier wichtig weil C-Compiler = geistig behindert
#include "Steuerung.h"
#include "Scan.h"
#include "Webserver.h"


void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
  displayInit();
  if (server_en) webserverInit();
  
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
  motorInit();
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
}

void loop() {
  dauerScan(15);
  displayDatenSchreiben();
  webserverClientUeberpruefen();
  
  if(kurz){
    scan(45);
    if(kurz == true){
      rueckwaertsfahren();
    }
    if(kurz == false){
      if (rd > ld){ 
        kurvefahren(r);
      }
      else if(ld > rd){
        kurvefahren(l);
      }
      else{
        kurvefahren(r);
      }
      geradeausfahren();
    }  
  } 
}
