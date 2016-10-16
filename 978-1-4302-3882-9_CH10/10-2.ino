void setup() {
  pinMode(9, OUTPUT); // IR emitter enable
  pinMode(13, OUTPUT); // LED pin
  digitalWrite(14, HIGH); // enable pullup on analog input A0/D14
}

void loop() {
  int infrared; // how much infrared: 0=none, 1023= a lot
  int threshold; // adjustable comparison value
  
  digitalWrite(9, HIGH); // enable infrared emitter
  threshold = 1023 - analogRead(1); // get threshold value
  infrared = 1023 - analogRead(0); // convert voltage
  digitalWrite(9, LOW); // disable infrared emitter
  
  if(infrared > threshold) {
    digitalWrite(13, HIGH); // LED on = IR detected
  } else {
    digitalWrite(13, LOW); // LED off = no IR detected
  }
}
