void setup() {
  bitSet(DDRB, 5); // PB5/D13 has an LED attached
  TCCR1A = 0;
  TCCR1B = 1<<CS12;
  bitSet(TIMSK1, TOIE1); // enable overflow interrupt
}

void loop() {
  // nothing happens here
}

ISR(TIMER1_OVF_vect) {
  bitSet(PINB, 5); // toggle LED
}
