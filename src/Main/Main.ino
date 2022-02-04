boolean  server_en = false; // Webserver Hauptschalter

#include "Lidar.h"
#include "Display.h"
#include "Webserver.h"        // Reihenfolge hier wichtig weil C-Compiler = geistig behindert
#include "Steuerung.h"
#include "Scan.h"

void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
  displayInit();
  if (server_en) webserverInit();
  motorInit();
}

void loop() {
  dauerScan(15);
  displayDatenSchreiben();

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
  
}
