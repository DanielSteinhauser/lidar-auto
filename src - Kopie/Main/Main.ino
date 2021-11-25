#include "Lidar.h"
#include "Display.h"
#include "Steuerung.h"


void setup() {
  kurz = false;
  Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, 470E6 /**/);    //todo: rausfinden wie zum Fick man diese Scheiß Library benutzt
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);

}

void loop() {
  
  dauerscannStepper();
  
 if(kurz){
    int n = 0;
    
    for(int i = 0; i <= 45; ++i){
      stepperBewegen(true);
      distanzMessen();
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist);
    }
    
    for(int i = 0; i <= 90; ++i){
      stepperBewegen(false);
      if(i>=45){
          distanzMessen();
          Serial.print("Stepp: ");
          Serial.print(i-45);
          Serial.print(" Distanz: ");
          Serial.println(dist);
      }
     }
    
    for(int i = 0; i <= 44; ++i){
        stepperBewegen(true);
    }
    
    kurz = false;
 }
 
}
