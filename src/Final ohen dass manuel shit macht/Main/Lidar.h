//Steuert LIDAR-Sensor
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
