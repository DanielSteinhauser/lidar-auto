void setup() {
  pinMode(12,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
}

void loop() {
 digitalWrite(12, HIGH);
 digitalWrite(14, LOW);
 digitalWrite(26, LOW);
 digitalWrite(27, HIGH);
}
