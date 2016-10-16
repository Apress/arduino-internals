void setup() {
  bitSet(TCCR2B, CS21); // change Timer/Counter2 prescaler to CK/256
  bitSet(TIMSK2, TOIE2); // enable Timer/counter2 overflow interrupt
}

void loop() {
  // nothing happens here
}

ISR(TIMER2_OVF_vect) {
  analogWrite(11, analogRead(0) >> 2);
  analogWrite(10, analogRead(1) >> 2);
  analogWrite(9, analogRead(2) >> 2);
  analogWrite(6, analogRead(3) >> 2);
  analogWrite(5, analogRead(4) >> 2);
  analogWrite(3, analogRead(5) >> 2);
}
