//Steuert Schrittmotor, Motoren
#include <Stepper.h>
int sped = 100;
int aus = 0;


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
 ledcWrite(0, sped);
 ledcWrite(1, aus);
 ledcWrite(2, aus);
 ledcWrite(3, sped);
}

void anhalten(){
 ledcWrite(0, aus);
 ledcWrite(1, aus);
 ledcWrite(2, aus);
 ledcWrite(3, aus);
}

void rueckwaertsfahren(){
  ledcWrite(0, aus);
  ledcWrite(1, sped);
  ledcWrite(2, sped);
  ledcWrite(3, aus);
 delay(3000);
 anhalten();
}

void kurvefahren(int n){
  double time = abs(n) * 8.333;
  if(n > 0){
   ledcWrite(0, aus);
   ledcWrite(1, aus);
   ledcWrite(2, aus);
   ledcWrite(3, sped);
  delay(time);
  anhalten();
  }else{
   ledcWrite(0, sped);
   ledcWrite(1, aus);
   ledcWrite(2, aus);
   ledcWrite(3, aus);
  delay(time);
  anhalten();
}
}

/*
void motorInit(){
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);
}
*/
