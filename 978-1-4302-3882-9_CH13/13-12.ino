void setup() {
  digitalWrite(5, HIGH); // enable pullup resistor for D5/PD5/T1 for tachometer input
  // timer/counter1 counts fan tachometer pulses on rising edge of T1, 2 per revolution
  TCCR1A = 0<<WGM11 | 0<<WGM10;
  TCCR1B = 0<<WGM13 | 0<<WGM12 | 1<<CS12 | 1<<CS11 | 1<<CS10;
  // timer/counter2 provides 125 interrupts per second
  TCCR2A = 1<<WGM21 | 0<<WGM20;
  TCCR2B = 0<<WGM22 | 1<<CS22 | 1<<CS21 | 1<<CS20;
  OCR2A = 124; // n-1
  TIMSK2 = 1<<OCIE2A; // enable compare match interrupt
  Serial.begin(9600);
  Serial.println("Fan Speed in RPM");
}

unsigned int fan_odometer = 0; // count of fan tachometer ticks
volatile byte update_flag = 0; // used to signal update of odometer reading

void loop() {
  static unsigned int previous_fan_odometer = 0;
  while(update_flag == 0); // wait for update to occur
  update_flag = 0; // reset update flag
  Serial.println(((fan_odometer - previous_fan_odometer) * 60) / 2); // in RPM
  previous_fan_odometer = fan_odometer;
}

ISR(TIMER2_COMPA_vect) {
  static byte prescaler;
  if(prescaler) {
    prescaler--;
  } else {
    prescaler = 125; // reset prescaler
    fan_odometer = TCNT1; // capture odometer reading
    update_flag = 1; // set flag
  }
}
