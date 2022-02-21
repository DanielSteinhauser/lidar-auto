//Steuert LIDAR-Sensor

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
//#define TFL_DEF_ADR          0x10
//#define TFL_DEF_FPS          0x64 

short dist;
int check;
int uart[9];
const int HEADER=0x59;
boolean kurz;
int dd;
TFLI2C tflI2C;
void distanzMessen(){
  tflI2C.getData(dist, byte(0x10));

//  Wire.beginTransmission(0x10);
//   
//   if(Serial2.available()){
//
//    if(Serial2.read()==HEADER){
//      uart[0]=HEADER;
//
//      if(Serial2.read()==HEADER){
//        uart[1]=HEADER;
//        for(int i=2; i<9;i++){
//          uart[i]=Serial2.read();
//        }
//
//        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
//
//        if(uart[8]==(check & 0xff)){
//          dist = uart[2]+uart[3]*256;
//        }
//      }
//    }
//  }
  return;
}
/*void dauerDistanzMessen(){
   if(!(Serial2.available())){
    Serial2.begin(115200,SERIAL_8N1,22,23);
   }
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
}*/
