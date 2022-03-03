//Steuert Schrittmotor, Motoren
int sped = 130;
int aus = 0;

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

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
 Serial.println("anhalten");
}



void kurvefahren(int n){
  Serial.print("kurve mit n:");
  Serial.println(n);
  double time = abs(n) * 8.33;
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
void rueckwaertsfahren(){
  kurvefahren(180);
  Serial.println("Rückwerts");
}
