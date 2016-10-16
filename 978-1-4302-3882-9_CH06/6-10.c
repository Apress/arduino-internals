while(timer0_millis < stop_time) {
  bitSet(PINB, 5); // toggle LED
  i++; // count!
}
