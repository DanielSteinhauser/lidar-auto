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
              
     case 1:  // autonomes fahren
              clearDisplay();
              aufDisplayAnzeigen(0, 0, "Autonomes Fahren");
              horizontaleLinie(11);
              
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
                    if (rechtskurveDistanz > linkskurveDistanz && rechtskurveGrad >= 0){ 
                      kurvefahren(rechtskurveGrad);
                      Serial.print("R");
                      delay(100);
                    }
                    // Wenn Linksdistanz größer wie Rechtsdistanz
                    else if(linkskurveDistanz > rechtskurveDistanz && linkskurveGrad <= 0){
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
                rechtskurveDistanz = 0;
                linkskurveDistanz = 0;
                rechtskurveGrad = 0;
                linkskurveGrad = 0;  
              }
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
            aufDisplayAnzeigen(0,20,"Test beendet, stop");
            
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
