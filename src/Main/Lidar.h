//Steuert LIDAR-Sensor

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

short dist;
byte tfAddr = TFL_DEF_ADR;
boolean kurz;
TFLI2C tflI2C;

void distanzMessen(){
  if(tflI2C.Set_Trigger(tfAddr)){
    delay(50);
    if(tflI2C.getData(dist, tfAddr)){  
      Serial.print("Dist: ");
      Serial.println(dist); 
    }
    else{
      tflI2C.printStatus();
    }  
  }
  else{
    Serial.println("Trigger ERROR! ");
  }
 
}
