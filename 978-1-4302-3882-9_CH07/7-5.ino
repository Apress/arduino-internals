void setup() {
  bitSet(DDRB, 5); // LED on PB5/D13
  TCCR1A = 0;
  TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS12 | 1<<CS10;
  ICR1 = 15625;
  bitSet(TIMSK1, ICIE1); // enable capture event interrupt
}

void loop() {
  // nothing happens here
}

ISR(TIMER1_CAPT_vect) {
  bitSet(PINB, 5); // toggle LED
}
