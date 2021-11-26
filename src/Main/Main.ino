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
  
  scanStepper(15);
  
  if(kurz){
    int n = 0;
    
    scanStepper(45);
    kurz = false;
  }
 
}
