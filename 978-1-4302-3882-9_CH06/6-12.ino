void setup() {
  bitSet(DDRB, 5); // PB5/D13 is connected to an LED
}

void loop() {
  bitSet(PINB, 5); // toggle LED
}
