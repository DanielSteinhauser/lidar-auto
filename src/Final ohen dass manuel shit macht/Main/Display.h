//Steuert Display

void clearDisplay() {   //Cleart Display
    Heltec.display->clear();
    Heltec.display->display();
}

void displayInit(){   //Initialisiert Display
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false /*Serial Enable*/, false /*PABOOST Enable*/, 470E6 /**/); 
    delay(500);
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->setColor(WHITE);
    Heltec.display->clear();
    Heltec.display->display();
}

void aufDisplayAnzeigen(int x, int y, String text) {  //Zeigt beliebigen String an gewählter Stelle an
    Heltec.display->drawString(x, y, text);
    Heltec.display->display();
}

void horizontaleLinie(int y) {
    Heltec.display->drawLine(0, y, 127, y);
    Heltec.display->display();
}
