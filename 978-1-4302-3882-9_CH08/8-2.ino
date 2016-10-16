void setup() {
}

void loop() {
  analogWrite(11, analogRead(0) >> 2);
  analogWrite(10, analogRead(1) >> 2);
  analogWrite(9, analogRead(2) >> 2);
  analogWrite(6, analogRead(3) >> 2);
  analogWrite(5, analogRead(4) >> 2);
  analogWrite(3, analogRead(5) >> 2);
}
