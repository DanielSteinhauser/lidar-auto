#include <Stepper.h>

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

int empfangeneInt = 0;
Stepper stepper (4096,IN1, IN3, IN2, IN4);

void setup() {
  stepper.setSpeed(5);
  Serial.begin(115200);
}

void loop() {
   if (Serial.available() > 1) {        //mind. 2 Byte im Empfangspuffer
      empfangeneInt = Serial.parseInt();//Zahl lesen und zurueckgeben und Empfangspuffer so weit loeschen   
      stepper.step(empfangeneInt);
      
      Serial.print("Ausgeführte Steps: ");
      Serial.println(empfangeneInt);    //Ausgabe der Integerzahl
   }
}
