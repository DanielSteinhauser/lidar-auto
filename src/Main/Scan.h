int rd = 0;
int ld = 0;
int r = 0;
int l = 0;
void scan(int grad){
 
  scanRechts(grad);
  scanResetRechts(grad);
  scanLinks(grad);
  scanResetLinks(grad);

  if(rd == 0 && ld == 0){
    kurz true;
    return;
  }
  else if (){
  }
}
double scanRechts(int grad)
{  // Scan rechts
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(true);
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
      if(n == 15)
      { rd = dist;
        kurvefahren(i-(7.5));
        kurz = false
      }
  }
}
double scanLinks()
{   // Scann links
   for(int i = 0; i <= grad; ++i){
      stepperBewegen(false);
      distanzMessen();
      ++n;
      if(dist <= 20 && dist > 0){
        anhalten();
        kurz = true;
        n = 0;
      }
      
      displayDatenSchreiben();
      
      Serial.print("Stepp: ");
      Serial.print(i-grad);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      if(n == 15)
      { ld = dist;
        kurvefahren((i*(-1))+(7.5));
        kurz = false;
      }
   }
}
void scanResetRechts(int grad)
{// Scan reset 
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(false);
      distanzMessen();
      //--n;
      if(dist <= 20 && dist > 0){
        anhalten();
        kurz = true;
        n = 0;
      }
      
      displayDatenSchreiben();
      
      Serial.print("Stepp: ");
      Serial.print(i-grad);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      /*if(n == -15)
      { kurvefahren(i-(7.5));
      }*/
      
   }
}

void scanResetLinks(int grad)
{  // Scan reset
   for(int i = 0; i <= grad-1; ++i){
      stepperBewegen(true);
      distanzMessen();
      //++n;
      
      displayDatenSchreiben();
      Serial.print("Stepp: ");
      Serial.print(i-grad);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      
      
      if(dist <= 20 && dist > 0){
        anhalten();
        kurz = true;
      }
      /*if(n == 15)
      { kurvefahren(i-(7.5));
      }*/
   }
}
