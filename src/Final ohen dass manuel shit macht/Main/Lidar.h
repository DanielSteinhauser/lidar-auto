//Steuert LIDAR-Sensor
TFLI2C luna;
int16_t tfDist;
int16_t tfAddr = TFL_DEF_ADR;
bool LidarReset;
bool triggermode;
bool distanzZuKurz;

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
