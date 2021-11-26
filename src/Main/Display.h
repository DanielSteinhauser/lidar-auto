//Steuert Display

#include <heltec.h>
void displayInit(){
  Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, 470E6 /**/); 
  delay(500);
  Heltec.display->clear();
  Heltec.display->display();
}
void displayDatenSchreiben(){
  
  Heltec.display->clear();
  Heltec.display->display();
  
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "kurz:");
  Heltec.display->drawString(30, 0, String(kurz));
  Heltec.display->drawString(0, 25, "dist:");
  Heltec.display->drawString(30, 25, String(dist));
  
  Heltec.display->display();

}
