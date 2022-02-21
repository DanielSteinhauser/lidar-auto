boolean mqtt_en = true; // MQTT Hauptschalter
boolean wlan_verbunden = false; // WLAN Zustand (nicht manuell ändern)

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
  ledcSetup(0, 128, 8);
  ledcSetup(1, 128, 8);
  ledcSetup(2, 128, 8);
  ledcSetup(3, 128, 8);
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
//  motorInit();
  clearDisplay();
  aufDisplayAnzeigen(0, 0, "Startzustand:");
  aufDisplayAnzeigen(0, 10, String(zustand));
  delay(1000);
}

void loop() {
  
  mqttAbrufen();

  switch (zustand){
     case 0: // ruhezustand
              clearDisplay();
              aufDisplayAnzeigen(0,20,"aktueller Zustand: 0");
              anhalten();
              break;

              
     case 1:  // autonomes fahren
              clearDisplay();
              aufDisplayAnzeigen(0,60,"aktueller Zustand: 1");
              dauerScan(8);
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
              clearDisplay();
              break;
              
     case 2:  
            clearDisplay();
            aufDisplayAnzeigen(0,20,"aktueller Zustand: 2");

            
            geradeausfahren();
            aufDisplayAnzeigen(0,50,"geradeaus");
              delay(2000);
            anhalten();
              delay(1000);

            clearDisplay();
            aufDisplayAnzeigen(0,50,"rückwärts");
            
            rueckwaertsfahren();
              delay(1000);
            
            clearDisplay();
            aufDisplayAnzeigen(0,50,"linkskurve");
            
            kurvefahren(-40);
              delay(2000);
            anhalten();
              delay(1000);
              
            clearDisplay();
            aufDisplayAnzeigen(0,50,"rechtskurve");
            
            kurvefahren(40);
              delay(2000);
            anhalten();
              delay(1000);


            break; //manuelles fahren
  }
}
