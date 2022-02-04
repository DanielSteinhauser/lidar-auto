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
<<<<<<< Updated upstream
  displayInit();
  if (server_en) webserverInit();
  geradeausfahren();
>>>>>>> Stashed changes
=======
  Serial.println("Geradeaus");
  geradeausfahren();
>>>>>>> Stashed changes
}



void loop() {
  scanStepper(15);
  displayDatenSchreiben();
  
  if(kurz){
<<<<<<< Updated upstream
    scanStepper(45);
    kurz = false;
=======
    scan(45);
    // Wenn immer noch Kurz 
    /*if(kurz == true){
      Serial.println("Rückwärts");
      rueckwaertsfahren();
    }*/
    //Wenn Kurvemöglichkeit gefunden
    if(kurz == false){
      // Wenn Rechtsdistanz größer wie Linksdistanz
      if (rd > ld){ 
        Serial.println("Rechtskurve");
        kurvefahren(r);
      }
      // Wenn Linksdistanz größer wie Rechtsdistanz
      else if(ld > rd){
        Serial.println("Linkskurve");
        kurvefahren(l);
      }
      // Wenn beide gleich groß sind
      else{
        Serial.println("Rechtskurve beide Kurven gleich");
        kurvefahren(r);
      }
      // Nach der Kurve weiter fahren
      Serial.println("Kurve fertig. Geradeaus");
      geradeausfahren();
    }  
>>>>>>> Stashed changes
  }
 
}
