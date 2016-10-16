void setup() {
}

void loop() {
  unsigned int adjust;
  adjust = analogRead(0); // read potentiometer setting
  adjust = map(adjust, 0, 1023, 0, 255); // scale for PWM output
  analogWrite(3, adjust); // set PWM duty cycle
  delay(50);
}
