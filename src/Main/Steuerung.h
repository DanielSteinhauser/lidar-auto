//Steuert Schrittmotor, Motoren
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
 ledcWrite(0, geschwindigkeit);
 ledcWrite(1, aus);
 ledcWrite(2, aus);
 ledcWrite(3, geschwindigkeit);
 Serial.println("geradeaus");
}

void anhalten(){
 ledcWrite(0, aus);
 ledcWrite(1, aus);
 ledcWrite(2, aus);
 ledcWrite(3, aus);
 Serial.println("anhalten");
}



void kurvefahren(int grad){
  Serial.print("kurve mit Grad = ");
  Serial.println(grad);
  double time = abs(grad) * 8.33;
  if(grad > 0){
   ledcWrite(0, aus);
   ledcWrite(1, aus);
   ledcWrite(2, aus);
   ledcWrite(3, geschwindigkeit);
  delay(time);
  anhalten();
  }else{
   ledcWrite(0, geschwindigkeit);
   ledcWrite(1, aus);
   ledcWrite(2, aus);
   ledcWrite(3, aus);
  delay(time);
  anhalten();
}
}
void umdrehen(){
  Serial.println("Umdrehen");
  kurvefahren(180);
}
