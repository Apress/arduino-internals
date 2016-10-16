ISR(TIMER2_OVF_vect) {
  
  static byte channel = 0;
  const byte pwm_pins[6] = { 11, 10, 9, 6, 5, 3 };
  
  analogWrite(pwm_pins[channel], analogRead(channel) >> 2);
  channel++;
  if(channel > 5) channel = 0; // roll over
}
