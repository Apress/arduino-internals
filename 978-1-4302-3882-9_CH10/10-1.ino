void setup() {
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(14, HIGH); // enable pullup on analog input A0/D14
}

void loop() {
  if(analogRead(0) < 900) {
    digitalWrite(13, HIGH); // LED on = IR detected
    delay(100); // stretch...
  } else {
    digitalWrite(13, LOW); // LED off = no IR detected
  }
}
