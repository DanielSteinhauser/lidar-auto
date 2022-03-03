//Steuert Display
void aufDisplayAnzeigen(int x, int y, String text) {
  Heltec.display->drawString(x, y, text);
  Heltec.display->display();
}

void clearDisplay() {
  Heltec.display->clear();
  Heltec.display->display();
}

void displayInit(){
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/, false /*PABOOST Enable*/, 470E6 /**/); 
  delay(500);
  clearDisplay();
}

void displayDatenSchreiben(){
  clearDisplay();
  
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "kurz:");
  Heltec.display->drawString(30, 0, String(kurz));
  Heltec.display->drawString(0, 25, "dist:");
  Heltec.display->drawString(30, 25, String(tfDist));

  Heltec.display->display();

}
