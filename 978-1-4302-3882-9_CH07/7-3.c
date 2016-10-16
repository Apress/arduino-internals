Serial.begin(9600);
bitSet(PCICR, PCIE0); // enable pin change interrupt bank 0
bitSet(PCMSK0, PCINT5); // enable pin change interrupt on PCINT5/D13

ISR(PCINT0_vect) {
  if(digitalRead(13) == HIGH) {
    Serial.println("LED is on");
  } else {
    Serial.println("LED is off");
  }
}
