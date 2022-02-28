/* File Name: TFLI2C_simple.ino
 * Developer: Bud Ryerson
 * Date:      4 NOV 2021
 * Version:   0.1.2
 * Described: Simplified Arduino example sketch for the Benewake
 *            TF-Luna LiDAR sensor configured for the I2C interface
 */
 
#include <Stepper.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <heltec.h>
#include <Arduino.h>  
#include <Wire.h>
#include <TFLI2C.h>

TFLI2C tflI2C;

int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // use this default I2C address or
bool reset;  
bool triggermode;// set variable to your own value

void setup()
{   
    ledcSetup(0, 128, 8);
    ledcSetup(1, 128, 8);
    ledcSetup(2, 128, 8);
    ledcSetup(3, 128, 8);
    ledcAttachPin(12, 0);
    ledcAttachPin(14, 1);
    ledcAttachPin(26, 2);
    ledcAttachPin(27, 3);
    Serial.begin(115200);  // initialize serial port
    Wire.begin(23, 22);           // initialize Wire library
    Serial.println( "TFLI2C example code simplified"); // say "Hello!"
    Serial.println( "4 NOV 2021");
    reset = tflI2C.Hard_Reset(tfAddr); 
    triggermode = tflI2C.Set_Trig_Mode(tfAddr);// and add date
}

void loop()
{   Serial.println(reset);   
    Serial.println(triggermode);
    if(tflI2C.Set_Trigger(tfAddr)){
      if( tflI2C.getData(tfDist, tfAddr)) // If read okay...
      {
          Serial.print("Dist: ");
          Serial.println(tfDist);          // print the data...
      }
      else tflI2C.printStatus();  
    }
    else Serial.println("Error");
    delay(3000);
}
