int rechtskurvenDistanz = 0;
int linkskurvenDistanz = 0;

int rechtskurveGrad = 0;
int linkskurveGrad = 0;

// Scan Funktion die Scannt und werte für eine mögliche Kurve gibt
void scanFuerKurve(int grad, boolean richtung){ 
  int anzahlGuterGrad = 0;
  for(int i = 0; i <= grad; ++i){
      distanzMessen();
      // Zählt index n eins hoch
      ++anzahlGuterGrad;
      if(tfDist <= 30 && tfDist > 0){
        distanzZuKurz = true;
        // Resettet n auf null , da distanz zu kurz
        anzahlGuterGrad = 0;
        if(richtung == true){ 
          rechtskurvenDistanz = 0;
        }
        else{ 
          linkskurvenDistanz = 0;
        }
      }
      stepperBewegen(richtung);
      Serial.print("Stepp: ");
      Serial.print(i);
      // setzt Rechtskurven Distanz
      if(anzahlGuterGrad > 0 && richtung == true){ 
        rechtskurvenDistanz += tfDist;
      }
      // setzt Linkskurven Distanz
      if(anzahlGuterGrad > 0 && richtung == false){ 
        linkskurvenDistanz += tfDist;
      }
      // Rechnet Grad für Rechtskurve aus und speichert es
      if(anzahlGuterGrad >= 10 && richtung == true){ 
        rechtskurveGrad = i-5;
      }
      // Rechnet Grad für Linkskurve aus und speichert es 
      if(anzahlGuterGrad >= 10 && richtung == false){ 
        linkskurveGrad = -(i-5);
      }
      //displayDatenSchreiben();
      if(rechtskurveGrad > 0 ||  linkskurveGrad < 0){
        distanzZuKurz = false;
      }
  }
  return;
}
void resetStepper(int grad, boolean richtung){ 
  for(int i = 0; i <= grad; ++i){
    stepperBewegen(richtung);
  }
  return;
}

// Scan das nach werte eine für Kurve sucht
void scanWennKurz(int grad){
  scanFuerKurve(grad, true);
  resetStepper(grad, false);
  scanFuerKurve(grad, false);
  resetStepper(grad, true);
  return;
}

// Dauerscan das nur das Auto anhalten soll
void dauerScan(){ 
  distanzMessen();
  Serial.print("Input: ");
  Serial.println(digitalRead(34));
  if(tfDist <= 30 && tfDist > 0){
    anhalten();
    distanzZuKurz = true;
  }
  Serial.print("Kurz: ");
  Serial.println(distanzZuKurz);
  return;
}
