#include "Includes.h"

void setup() {
  Serial.begin(115200);
  displayInit(); //begin heltec   
  Serial.println("LIDAR reset: " + String(luna.Hard_Reset(tfAddr)));
  if (mqtt_en) mqttInit();
  clearDisplay();
  aufDisplayAnzeigen(0, 0, "Startzustand:");
  aufDisplayAnzeigen(0, 10, String(zustand));  
  Serial.print("Triggermode: ");
  Serial.println(luna.Set_Trig_Mode(tfAddr));
  stepper.setSpeed(5);
  
  ledcSetup(0, 128, 8);
  ledcSetup(1, 128, 8);
  ledcSetup(2, 128, 8);
  ledcSetup(3, 128, 8);
  ledcAttachPin(12, 0);
  ledcAttachPin(14, 1);
  ledcAttachPin(26, 2);
  ledcAttachPin(27, 3);

  delay(1000);
}

void loop() {
  mqttAbrufen();

  switch (zustand){
     case 0: // ruhezustand
              clearDisplay();
              aufDisplayAnzeigen(0,30,"aktueller Zustand: 0");
              anhalten();
              break;         
     case 1:  // autonomes fahren
              clearDisplay();
              aufDisplayAnzeigen(0,30,"aktueller Zustand: 1");
              dauerScan();
              if(distanzZuKurz == false){
                geradeausfahren();
              }           
              if(distanzZuKurz){
                scanWennKurz(45);
                // Wenn immer noch Kurz 
                if(distanzZuKurz){
                  umdrehen();
                }
                //Wenn Kurvemöglichkeit gefunden
                else if(distanzZuKurz == false){
                    // Wenn Rechtsdistanz größer wie Linksdistanz
                    if (rechtskurvenDistanz > linkskurvenDistanz && rechtskurveGrad >= 0){ 
                      kurvefahren(rechtskurveGrad);
                      Serial.print("R");
                      delay(100);
                    }
                    // Wenn Linksdistanz größer wie Rechtsdistanz
                    else if(linkskurvenDistanz > rechtskurvenDistanz && linkskurveGrad <= 0){
                      kurvefahren(linkskurveGrad);
                      Serial.print("L");
                      delay(100);
                    }
                    // Wenn beide gleich groß sind
                    else if(rechtskurveGrad >= 0){
                      kurvefahren(rechtskurveGrad);
                      delay(100);
                      Serial.print("R,R");
                    } 
                }
                // Nach der Kurve weiter fahren
                rechtskurvenDistanz = 0;
                linkskurvenDistanz = 0;
                rechtskurveGrad = 0;
                linkskurveGrad = 0;  
              }
              clearDisplay();
              break;              
     case 2:  
//            clearDisplay();
//            aufDisplayAnzeigen(0,30,"aktueller Zustand: 2");
//
//            
//            geradeausfahren();
//            aufDisplayAnzeigen(0,50,"geradeaus");
//              delay(2000);
//            anhalten();
//              delay(1000);
//
//            clearDisplay();
//            aufDisplayAnzeigen(0,50,"rückwärts");
//            
//            rueckwaertsfahren();
//              delay(1000);
//            
//            clearDisplay();
//            aufDisplayAnzeigen(0,50,"linkskurve");
//            
//            kurvefahren(-40);
//              delay(2000);
//            anhalten();
//              delay(1000);
//              
//            clearDisplay();
//            aufDisplayAnzeigen(0,50,"rechtskurve");
//            
//            kurvefahren(40);
//              delay(2000);
//            anhalten();
//              delay(1000);
//            break; //manuelles fahren
              ledcWrite(0, geschwindigkeit);
              ledcWrite(1, aus);
              ledcWrite(2, aus);
              ledcWrite(3, aus);
  }
}
