// Scan Funktion die Scannt und werte für eine mögliche Kurve gibt
void scanen(int grad, boolean richtung)
{ int n = 0;
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(richtung);
      distanzMessen();
      ++n;
      if(dist <= 20 && dist > 0){
        anhalten();
        kurz = true;
        n = 0;
      }
      displayDatenSchreiben();
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      // setzt Rechtskurven Distanz
      if(n == 8 && richtung == true){ 
        rd = dist;
      }
      // setzt Linkskurven Distanz
      else if(n == 8 && richtung == false){ 
        ld = dist;
      }
      // 
      if(n == 16 && richtung == true){ 
        r = i-8;
        kurz = false;
      }
      if(n == 16 && richtung == false){ 
        l = (i-8)*(-1);
        kurz = false;
      }
  }
}
// Scan Funktion die nur Scannt, anhält und keine Werte liefert
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

void scan(int grad){
  scanen(grad, true);
  reset(grad, false);
  scanen(grad, false);
  reset(grad, true);
}

void dauerScan(int grad)
{ reset(grad, true);
  reset(grad, false);
  reset(grad, false);
  reset(grad, true);
}
