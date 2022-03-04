//Steuert LIDAR-Sensor
TFLI2C luna;
int16_t tfDist;
int16_t tfAddr = TFL_DEF_ADR;
bool distanzZuKurz = false;
bool LidarReset = luna.Hard_Reset(tfAddr);
bool triggermode = luna.Set_Trig_Mode(tfAddr);

void distanzMessen(){
  if(luna.Set_Trigger(tfAddr)){
    if(luna.getData(tfDist, tfAddr))
    { Serial.print("Dist: ");
      Serial.println(tfDist);
    }
    else luna.printStatus();  
  }
  else Serial.println("Trigger ERROR!!!");
  delay(50);
  return;
}
