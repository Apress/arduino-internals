void setup() {
}

void loop() {

  static byte pwm = 0;

  analogWrite(11, pwm); // set the PWM duty cycle
  delay(10); // a very short delay
  pwm++; // increase the PWM duty cycle
}
