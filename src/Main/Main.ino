boolean  mqtt_en = true; // MQTT Hauptschalter

int zustand = 0; //Startzustand
// zustand 0: warten auf befehle, ruhe
// zustand 1: autonomes fahren
// zustand 2: manuelle Steuerung


#include "Lidar.h"
#include "Display.h"
#include "MQTT.h"        // Reihenfolge hier wichtig weil C-Compiler = geistig behindert
#include "Steuerung.h"
#include "Scan.h"


void setup() {
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);
  ledcAttachPin(12, 0);
  ledcAttachPin(14, 1);
  ledcAttachPin(26, 2);
  ledcAttachPin(27, 3);
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
  displayInit();
  if (mqtt_en) mqttInit();
  motorInit();
  clearDisplay();
  aufDisplayAnzeigen(0, 0, "Startzustand:");
  aufDisplayAnzeigen(0, 10, String(zustand));
  delay(1000);
}

void loop() {
  
  mqttAbrufen();

  switch (zustand){
     case 0: // ruhezustand
              anhalten();  
              break;

              
     case 1:  // autonomes fahren
              dauerScan(15);
              if(kurz == false){
                geradeausfahren();
              } 
            
              if(kurz){
                scan(45);
                // Wenn immer noch Kurz 
                if(kurz == true){
                  rueckwaertsfahren();
                }
                //Wenn Kurvemöglichkeit gefunden
                else if(kurz == false){
                    // Wenn Rechtsdistanz größer wie Linksdistanz
                    if (rd > ld){ 
                      kurvefahren(r);
                    }
                    // Wenn Linksdistanz größer wie Rechtsdistanz
                    else if(ld > rd){
                      kurvefahren(l);
                    }
                    // Wenn beide gleich groß sind
                    else{
                      kurvefahren(r);
                    } 
                }
                // Nach der Kurve weiter fahren
                geradeausfahren();
                rd = 0;
                ld = 0;
                r = 0;
                l = 0;  
              }
              break;
              
     case 2:  
            anhalten(); // PLACEHOLDER
            break; //manuelles fahren
  }
}
