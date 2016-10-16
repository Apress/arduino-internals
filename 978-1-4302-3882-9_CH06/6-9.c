while(timer0_millis < stop_time) {
  bitSet(PORTB, 5); // LED on
  bitClear(PORTB, 5); // LED off
  i++; // count!
}
