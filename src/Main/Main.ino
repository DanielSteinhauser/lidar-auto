#include "Lidar.h"
#include "Display.h"
#include "Steuerung.h"
#include "Webserver.h"

void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
  webserverInit();
  displayInit();
}



void loop() {
  scanStepper(15);
  displayDatenSchreiben();
  
  if(kurz){
    int n = 0;
    
    scanStepper(45);
    kurz = false;
  }
 
}
