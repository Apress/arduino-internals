void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  //pinMode(13, OUTPUT);     
  bitSet(DDRB, 5); // D13 (PB5) is now an output
}
