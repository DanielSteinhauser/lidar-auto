//Steuert Schrittmotor, Motoren


#include <Stepper.h>

Stepper stepper (4096,IN1, IN3, IN2, IN4);




void stepperBewegen(boolean uhrzeigersinn){
  if(uhrzeigersinn == true){
    stepper.step(11);
  }
  else if(uhrzeigersinn == false){
    stepper.step(-11);
  }

  return;
}

void geradeausfahren(){
 digitalWrite(12, HIGH);
 digitalWrite(14, LOW);
 digitalWrite(26, LOW);
 digitalWrite(27, HIGH);
}

void anhalten(){
 digitalWrite(12, LOW);
 digitalWrite(14, LOW);
 digitalWrite(26, LOW);
 digitalWrite(27, LOW);
}

void rueckwaertsfahren(){
 digitalWrite(12, LOW);
 digitalWrite(14, HIGH);
 digitalWrite(26, HIGH);
 digitalWrite(27, LOW);
}

void kurvefahren(double n){
  double time = abs(n) * 8.333;

{
  if(n < 0){
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
  delay(time);
  }else{
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
  delay(time);
}
}
}

void scanStepper(int grad){
  int n = 0;
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(true);
      distanzMessen();
      ++n;
    
      if(dist <= 10 && dist > 0){
        anhalten();
        kurz = true;
<<<<<<< Updated upstream
=======
        n = 0;
>>>>>>> Stashed changes
      }
      
      displayDatenSchreiben();
      
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      if(n == 15)
      { kurvefahren(i-(7.5));
        geradeausfahren();
      }
  }
  n = 0;
  for(int i = 0; i <= grad; ++i){
      stepperBewegen(false);
      distanzMessen();
      //--n;
      if(dist <= 10 && dist > 0){
        anhalten();
        kurz = true;
<<<<<<< Updated upstream
=======
        n = 0;
>>>>>>> Stashed changes
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
   n = 0;
   for(int i = 0; i <= grad; ++i){
      stepperBewegen(false);
      distanzMessen();
      ++n;
      if(dist <= 10 && dist > 0){
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
      { kurvefahren((i*(-1))+(7.5));
        geradeausfahren();
      }
   }
   n = 0;
   for(int i = 0; i <= grad-1; ++i){
      stepperBewegen(true);
      distanzMessen();
      //++n;
      
      displayDatenSchreiben();
      Serial.print("Stepp: ");
      Serial.print(i-grad);
      Serial.print(" Distanz: ");
      Serial.println(dist);
      
      
      if(dist <= 10 && dist > 0){
        anhalten();
        kurz = true;
      }
      /*if(n == 15)
      { kurvefahren(i-(7.5));
      }*/
   }
   return;
<<<<<<< Updated upstream
}

void fahren(int richtung, int grad){
  
}

void motorInit(){
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);  
=======
>>>>>>> Stashed changes
}
