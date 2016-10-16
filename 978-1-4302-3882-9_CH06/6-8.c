while(timer0_millis < stop_time) {
  digitalWrite(13, HIGH); // LED on
  digitalWrite(13, LOW); // LED off
  i++; // count!
}
