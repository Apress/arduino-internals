void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Uno as Thermometer");
  ADMUX = 1<<REFS1 | 1<<REFS0 | 1<<MUX3; // 1.1V reference, ADC channel "8"
  ADCSRA = 1<<ADEN | 1<<ADSC | 0x07; // enable ADC, start conversion, 125 KHz clock
}

#define OFFSET 343

void loop() {
  
  Serial.print(ADC - OFFSET);
  Serial.println("C");
  bitSet(ADCSRA, ADSC); // start next conversion
  delay(250); // wait
}
