int rd = 0;
int ld = 0;
int r = 0;
int l = 0;

// Scan Funktion die Scannt und werte für eine mögliche Kurve gibt
void scanen(int grad, boolean richtung)
{ int n = 0;
  for(int i = 0; i <= grad; ++i){
      distanzMessen();
      if(dist <= 30 && dist > 0){
        kurz = true;
        // Resettet n auf null , da distanz zu kurz
        n = 0;
      }
      stepperBewegen(richtung);
      
      // Zählt index n eins hoch
      ++n;
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
  Serial.print("Input: ")
  Serial.println(digitalRead(34));
  if(dist <= 30 && dist > 0){
    anhalten();
    kurz = true;
  }
  else{
  Serial.print(" Distanz: ");
  Serial.println(dist);
  }
  Serial.print(" Kurz: ");
  Serial.println(kurz);
  return;
}
