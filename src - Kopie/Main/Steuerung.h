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


void dauerscannStepper(){
  for(int i = 0; i <= 15; ++i){
      stepperBewegen(true);
      distanzMessen();
      if(dist <= 10){
        kurz = true;
      }
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist);

  }
  for(int i = 0; i <= 30; ++i){
      stepperBewegen(false);
      distanzMessen();
      if(dist <= 10){
        kurz = true;
      }
      if(i>=15){
        Serial.print("Stepp: ");
        Serial.print(i-15);
        Serial.print(" Distanz: ");
        Serial.println(dist);
      }
   }
   for(int i = 0; i <= 14; ++i){
      stepperBewegen(true);
      distanzMessen();
      if(dist <= 10){
        kurz = true;
      }
   }
   return;
}
