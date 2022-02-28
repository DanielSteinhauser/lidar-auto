int rd = 0;
int ld = 0;
int r = 0;
int l = 0;

// Scan Funktion die Scannt und werte für eine mögliche Kurve gibt
void scanen(int grad, boolean richtung)
{ int n = 0;
  for(int i = 0; i <= grad; ++i){
      distanzMessen();
      if(tfDist <= 30 && tfDist > 0){
        kurz = true;
        // Resettet n auf null , da distanz zu kurz
        n = 0;
      }
      stepperBewegen(richtung);
      
      // Zählt index n eins hoch
      ++n;
      Serial.print("Stepp: ");
      Serial.print(i);
      // setzt Rechtskurven Distanz
      if(n == 5 && richtung == true){ 
        rd = tfDist;
      }
      // setzt Linkskurven Distanz
      if(n == 5 && richtung == false){ 
        ld = tfDist;
      }
      // Rechnet Grad für Rechtskurve aus und speichert es
      if(n == 10 && richtung == true){ 
        r = i-(n/2);
      }
      // Rechnet Grad für Linkskurve aus und speichert es 
      if(n == 10 && richtung == false){ 
        l = -(i-(n/2));
      }
      //displayDatenSchreiben();
      if(r > 0 ||  l < 0){
        kurz = false;
      }
  }
  return;
}
void reset(int grad, boolean richtung){ 
  for(int i = 0; i <= grad; ++i){
    stepperBewegen(richtung);
  }
  return;
}
// Scan das nach werte eine für Kurve sucht
void scan(int grad){
  scanen(grad, true);
  reset(grad, false);
  scanen(grad, false);
  reset(grad, true);
  return;
}
// Dauerscan das nur das Auto anhalten soll
void dauerScan()
{ distanzMessen();
  Serial.print("Input: ");
  Serial.println(digitalRead(34));
  if(tfDist <= 30 && tfDist > 0){
    anhalten();
    kurz = true;
  }
  Serial.print("Kurz: ");
  Serial.println(kurz);
  return;
}
