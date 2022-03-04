bool mqtt_en = true; // MQTT Hauptschalter
bool wlan_verbunden = false; // WLAN Zustand (nicht manuell ändern)
int zustand = 0; //Startzustand
// zustand 0: warten auf befehle, ruhe
// zustand 1: autonomes fahren
// zustand 2: manuelle Steuerung
#include <Stepper.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <heltec.h>
#include <Arduino.h>  
#include <Wire.h>
#include <TFLI2C.h>
#include "Lidar.h"
#include "Display.h"
#include "MQTT.h"// Reihenfolge hier wichtig weil C-Compiler = geistig behindert
#include "Steuerung.h"
#include "Scan.h"

void setup() {
  Serial.begin(115200);
  displayInit(); //begin heltec
  
  LidarReset = luna.Hard_Reset(tfAddr);
  triggermode = luna.Set_Trig_Mode(tfAddr);
  
  pinMode(34, INPUT);
  
  ledcSetup(0, 128, 8);
  ledcSetup(1, 128, 8);
  ledcSetup(2, 128, 8);
  ledcSetup(3, 128, 8);
  ledcAttachPin(12, 0);
  ledcAttachPin(14, 1);
  ledcAttachPin(26, 2);
  ledcAttachPin(27, 3);
  
  distanzZuKurz = false;

  stepper.setSpeed(5);
  displayInit();
  if (mqtt_en) mqttInit();
  clearDisplay();
  aufDisplayAnzeigen(0, 0, "Startzustand:");
  aufDisplayAnzeigen(0, 10, String(zustand));
  delay(1000);
}

void loop() {
  Serial.print("Triggermode: ");
  Serial.println(triggermode);
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
