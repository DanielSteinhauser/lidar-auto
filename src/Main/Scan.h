int rd = 0;
int ld = 0;
int r = 0;
int l = 0;
// Scan Funktion die Scannt und werte für eine mögliche Kurve gibt
void scanen(int grad, boolean richtung)
{ int n = 0;
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(richtung);
      distanzMessen();
      // Zählt index n eins hoch
      ++n;
      if(dist <= 20 && dist > 0){
        anhalten();
        kurz = true;
        // Resettet n auf null , da distanz zu kurz
        n = 0;
      }
      displayDatenSchreiben();
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      // setzt Rechtskurven Distanz
      if(n == 5 && richtung == true){ 
        rd = dist;
      }
      // setzt Linkskurven Distanz
      if(n == 5 && richtung == false){ 
        ld = dist;
      }
      // Rechnet Grad für Rechtskurve aus und speichert es
      if(n == 10 && richtung == true){ 
        r = i-(i/2);
      }
      // Rechnet Grad für Linkskurve aus und speichert es 
      if(n == 10 && richtung == false){ 
        l = (i-(i/2))*(-1);
      }
      if(rd > 0 || ld > 0){
        kurz = false;
      }
  }
}
// Scan Funktion die nur Scannt, anhält und keine Werte ändert(außer kurz)
void reset(int grad, boolean richtung){ 
  for(int i = 0; i <= grad; ++i){
    stepperBewegen(richtung);
    distanzMessen();
    if(dist <= 20 && dist > 0){
    anhalten();
    kurz = true;
    }
    displayDatenSchreiben();
    Serial.print("Stepp: ");
    Serial.print(i);
    Serial.print(" Distanz: ");
    Serial.println(dist);
  }
}
// Scan das nach werte eine für Kurve sucht
void scan(int grad){
  scanen(grad, true);
  reset(grad, false);
  scanen(grad, false);
  reset(grad, true);
}
// Dauerscan das nur das Auto anhalten soll
void dauerScan(int grad)
{ reset(grad, true);
  reset(grad, false);
  reset(grad, false);
  reset(grad, true);
}
