void setup() {
  bitSet(DDRB, 5); // LED pin
  TCCR2A = 0; // normal mode
  TCCR2B = 5; // super slow CK/128
  TIMSK2 = 1<<OCIE2A | 1<<TOIE2; // enable match and overflow interrupts
}

byte pwm = 0;

void loop() {
  analogWrite(11, pwm); // set PWM duty cycle
  delay(10); // a short delay
  pwm++; // increase PWM duty cycle
}

ISR(TIMER2_OVF_vect) {
  if(pwm) bitSet(PORTB, 5); // LED on, maybe
}

ISR(TIMER2_COMPA_vect) {
  if(pwm < 255) bitClear(PORTB, 5); // LED off, maybe
}
