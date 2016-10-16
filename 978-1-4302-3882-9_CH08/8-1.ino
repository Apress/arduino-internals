void setup() {
}

void loop() {
  analogWrite(11, analogRead(0) >> 2);
}
