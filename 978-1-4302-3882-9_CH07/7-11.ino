#define SAMPLES 2500

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Automatic Voltmeter");
  ADMUX = 1<<REFS0; // select ADC0 (A0), AREF=AVCC (5.0V)
  ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADATE | 1<<ADIE | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
  ADCSRB = 0; // free running mode
  bitSet(DIDR0, ADC0D); // disable digital input on ADC0
}

void loop() {
  // nothing happens here
}

ISR(ADC_vect) {
  
  static unsigned int i = 0; // sample counter
  static unsigned long voltage = 0; // voltage reading accumulator

  voltage += ADC; // accumulate voltage readings
  i++; // also count samples taken
  ADMUX = 1<<REFS0; // re-select ADC0 (A0), AREF=AVCC (5.0V)
  
  if(i >= SAMPLES) {
    Serial.print((((voltage * 5.0) / 1024) / SAMPLES), 4); // report
    Serial.println("V"); // label units of measure
    voltage = 0; // reset voltage readings
    i = 0; // reset sample count
  }
}
