void setup() {
  // output ports
  DDRB = 0xFF; // all outputs
  DDRD = 0xFF; // all outputs
  // ADC
  ADMUX = 0<<REFS1 | 1<<REFS0 | 1<<ADLAR;
  ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
  DIDR0 = 1<<ADC5D | 1<<ADC4D | 1<<ADC3D | 1<<ADC2D | 1<<ADC1D | 1<<ADC0D;
  // Timer/counter0
  TCCR0A = 1<<COM0A1 | 0<<COM0A0 | 1<<COM0B1 | 0<<COM0B0 | 0<<WGM01 | 1<<WGM00;
  TCCR0B = 0<<WGM02 | 1<<CS02 | 0<<CS01 | 0<<CS00;
  // Timer/counter1
  TCCR1A = 1<<COM1A1 | 0<<COM1A0 | 1<<COM1B1 | 0<<COM1B0 | 0<<WGM11 | 1<<WGM10;
  TCCR1B = 0<<WGM13 | 0<<WGM12 | 1<<CS12 | 0<<CS11 | 0<<CS10;
  // Timer/counter2
  TCCR2A = 1<<COM2A1 | 0<<COM2A0 | 1<<COM2B1 | 0<<COM2B0 | 0<<WGM21 | 1<<WGM20;
  TCCR2B = 0<<WGM22 | 1<<CS22 | 1<<CS21 | 0<<CS20;
  bitSet(TIMSK2, TOIE2); // enable overflow interrupt
}

void loop() {
  // nothing happens here
}

ISR(TIMER2_OVF_vect) {
  
  static byte channel = 0;
  byte adc;

  adc = ADCH; // read upper 8 bits of ADC conversion result
  
  switch(channel) {
    case 0: OCR2A = adc; break; // PWM pin D11
    case 1: OCR1B = adc; break; // PWM pin D10
    case 2: OCR1A = adc; break; // PWM pin D9
    case 3: OCR0A = adc; break; // PWM pin D6
    case 4: OCR0B = adc; break; // PWM pin D5
    case 5: OCR2B = adc; break; // PWM pin D3
  }
  
  channel++;
  if(channel > 5) channel = 0;
  ADMUX = 0<<REFS1 | 1<<REFS0 | 1<<ADLAR | channel;
  ADCSRA = 1<<ADEN | 1<<ADSC | 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
}
