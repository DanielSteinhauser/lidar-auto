#include "Lidar.h"
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
}
void loop() {
              dauerScan(8);
              if(kurz == false){
                geradeausfahren();
              } 
            
              if(kurz){
                scan(45);
                if(r > 0 ||  l < 0){
                  kurz = false;
                }
                // Wenn immer noch Kurz 
                if(kurz == true){
                  //rueckwaertsfahren();
                  Serial.println("Rueckwertsfahren");
                }
                //Wenn Kurvemöglichkeit gefunden
                else if(kurz == false){
                    // Wenn Rechtsdistanz größer wie Linksdistanz
                    if (rd > ld){ 
                      //kurvefahren(r);
                      Serial.println("Rechtskurve");
                    }
                    // Wenn Linksdistanz größer wie Rechtsdistanz
                    else if(ld > rd){
                      //kurvefahren(l);
                      Serial.println("Linkskurve");
                    }
                    // Wenn beide gleich groß sind
                    else{
                      //kurvefahren(r);
                      Serial.println("Rechtskurve");
                    } 
                }
                // Nach der Kurve weiter fahren
                geradeausfahren();
                rd = 0;
                ld = 0;
                r = 0;
                l = 0;  
              }       
}
