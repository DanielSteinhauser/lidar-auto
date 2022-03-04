//globale Variablen
bool mqtt_en = true; // MQTT Hauptschalter
bool wlan_verbunden = false; // WLAN Zustand (nicht manuell ändern)
int zustand = 0; //Startzustand
int serialBefehl;

// Header
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
  displayInit(); //begin heltec klasse
  
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
  // Serial.print("Triggermode: ");
  // Serial.println(triggermode);
  mqttAbrufen();

  switch (zustand){
     case 0: // ruhemodus
              clearDisplay();
              aufDisplayAnzeigen(0,0,"Ruhemodus");
              horizontaleLinie(11);
              anhalten();
              
              if (WiFi.status() != WL_CONNECTED){
                  aufDisplayAnzeigen(0,12,"kein Internet !");
              }else{
                  aufDisplayAnzeigen(0,12,"warte auf MQTT-Befehle.");
              }
              
              break;
                       
     case 1:  // autonommodus
              clearDisplay();
              aufDisplayAnzeigen(0, 0, "Autonomes Fahren");
              horizontaleLinie(11);
              dauerScan();
              aufDisplayAnzeigen(0, 12, "Distanz:");
              aufDisplayAnzeigen(38, 12, String(tfDist));
              if(distanzZuKurz == false){
                geradeausfahren();
              }
              if(distanzZuKurz){
                aufDisplayAnzeigen(0, 23, "Hindernis entdeckt!");  // test
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

     case 2:  //manuell WIP
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Manuelle Steuerung");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,12,"warte auf MQTT-Befehle.");

            //hier manuelle variablen überprüfen
            break;     

     case 3:  //Motortest (wird nur einmal ausgeführt, danach rückkehr zu zustand 0 (Ruhemodus))
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"geradeaus");
            
            geradeausfahren();
              delay(2000);
              
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"stop");
            
            anhalten();
              delay(1000);
              
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"umdrehen");
            
            umdrehen();
              delay(1000);
            
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"stop");
            
            anhalten();
              delay(1000);
              
            
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"Kurve -40");
            
            kurvefahren(-40);
              delay(2000);
              
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"stop");
            
            anhalten();
              delay(1000);

            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"Kurve 40");
            
            kurvefahren(40);
              delay(2000);

            clearDisplay();
            aufDisplayAnzeigen(0,0,"Motortest");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,20,"Test beendet");
            
            anhalten();
              delay(1000);
              
            zustand = 0;
            break; 
            
      case 4:  //Stepper Kalibrierung
            clearDisplay();
            aufDisplayAnzeigen(0,0,"Stepper Kalibrierung");
            horizontaleLinie(11);
            aufDisplayAnzeigen(0,12,"warte auf Serial - Befehle.");
            
           if (Serial.available() > 1) {        //mind. 2 Byte im Empfangspuffer
              serialBefehl = Serial.parseInt();//Zahl lesen und zurueckgeben und Empfangspuffer so weit loeschen   
              stepper.step(serialBefehl);
              
              Serial.print("Ausgeführte Steps: ");
              Serial.println(serialBefehl);    //Ausgabe der Integerzahl
           }
            //hier manuelle variablen überprüfen
            break;     

  }
}
