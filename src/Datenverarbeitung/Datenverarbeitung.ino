#include <Stepper.h>
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
Stepper stepper (4096,IN1, IN3, IN2, IN4);
int dist;
int check;
int uart[9];
const int HEADER=0x59;
boolean kurz;

void setup() {
  kurz = false;
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
  stepper.setSpeed(5);
}

void loop() {
  dauerscannStepper();
  if(kurz){
    int n = 0;
    for(int i = 0; i <= 45; ++i){
      stepperBewegen(true);
      distanzMessen();
      Serial.print("Stepp: ");
      Serial.print(i);
      Serial.print(" Distanz: ");
      Serial.println(dist); 
    }
    for(int i = 0; i <= 90; ++i){
      stepperBewegen(false);
      if(i>=45){
        distanzMessen();
        Serial.print("Stepp: ");
        Serial.print(i-45);
        Serial.print(" Distanz: ");
        Serial.println(dist);
      }
    }
    for(int i = 0; i <= 44; ++i){
      stepperBewegen(true); 
    }
    kurz = false;      
  }
}

void distanzMessen(){
   if(Serial2.available()){ 
    
    if(Serial2.read()==HEADER){
      uart[0]=HEADER;
      
      if(Serial2.read()==HEADER){
        uart[1]=HEADER;
        for(int i=2; i<9;i++){
          uart[i]=Serial2.read();
        }
        
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        
        if(uart[8]==(check & 0xff)){
          dist = uart[2]+uart[3]*256;
        }
      }
    } 
  }
  return;
}
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
      if(i>=15){
        distanzMessen();
        if(dist <= 10){
          kurz = true;  
        }
        Serial.print("Stepp: ");
        Serial.print(i-15);
        Serial.print(" Distanz: ");
        Serial.println(dist);
        
      }
   }
   for(int i = 0; i <= 14; ++i){
      stepperBewegen(true); 
   } 
   return;
}
