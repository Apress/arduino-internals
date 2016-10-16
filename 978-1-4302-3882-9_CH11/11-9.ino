void setup() {
  DDRB = 0b00011111;
}

void delay(volatile unsigned long int i) {
  while(i) i--;
}

void loop() {
  for(PORTB = 1; PORTB < 32; PORTB<<=1) {
    delay(100000);
  }
  for(PORTB = 8; PORTB > 1; PORTB>>=1) {
    delay(100000);
  }
}
