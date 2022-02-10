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
 delay(3000);
 anhalten();
}

void kurvefahren(double n){
  double time = fabs(n) * 8.333;
  if(n > 0){
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, HIGH);
  delay(time);
  anhalten();
  }else{
    digitalWrite(12, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
  delay(time);
  anhalten();
}
}


void motorInit(){
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(26,OUTPUT);
}
