
int dist;
int check;
int i;
int uart[9];
const int HEADER=0x59;
boolean kurz;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,22,23);
}

void loop() {
  distanzMessen();
  Serial.print("Distanz: ");
  Serial.println(dist);
  if(dist <= 10){
    kurz = true;
    int n = 0;
    while(kurz){
      // Stepper
      Serial.println("Kurz");
      distanzMessen();
      
      if (dist > 10){
        ++n;
        Serial.println("Nicht kurz");
      }
      else{
        n = 0;
      }
      if(n == 100){
        kurz = false;
      }
    }   
       
  }

}

void distanzMessen(){
   if(Serial2.available()){ 
    
    if(Serial2.read()==HEADER){
      uart[0]=HEADER;
      
      if(Serial2.read()==HEADER){
        uart[1]=HEADER;
        for(i=2; i<9;i++){
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