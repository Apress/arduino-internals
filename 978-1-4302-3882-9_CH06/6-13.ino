void setup() {
  Serial.begin(9600);
  Serial.println("Normal serial communication at 9600 bps");

  pinMode(13, OUTPUT); // D13 is conneced to an LED

  noInterrupts(); // diable interrupts temporarily
  CLKPR = 1<<CLKPCE; // enable clock prescaler write sequence
  CLKPR = 8; // select clock divisor of 256
  interrupts(); // re-enable interrupts
}

void loop() {
  digitalWrite(13, HIGH); // LED is on
  delay(10); // 0.01 second delay
  digitalWrite(13, LOW); // LED is off
  delay(10); // 0.01 second delay
}
