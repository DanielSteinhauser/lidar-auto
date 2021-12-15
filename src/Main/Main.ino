#include "Lidar.h"
#include "Display.h"
#include "Webserver.h"        // Reihenfolge hier wichtig weil C-Compiler = geistig behindert
#include "Steuerung.h"


void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
  displayInit();
  webserverInit();
}



void loop() {
  scanStepper(15);
  displayDatenSchreiben();
  webserverClientUeberpruefen();
  
  if(kurz){
    int n = 0;
    
    scanStepper(45);
    kurz = false;
  }
 
}
