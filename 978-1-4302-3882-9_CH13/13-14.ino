volatile unsigned int left_odometer = 0, right_odometer = 0;

void setup() {
  pinMode(9, OUTPUT); // left servo PWM output
  pinMode(10, OUTPUT); // right servo PWM output
  Serial.begin(115200);
  Serial.println("*** Robot initializing ***");
  // timer/counter1 is used for servo PWM (mode 8) and system heartbeat
  TCCR1A = 1<<COM1A1 | 0<<COM1A0 | 1<<COM1B1 | 0<<COM1B0 | 0<<WGM11 | 0<<WGM10;
  TCCR1B = 1<<WGM13 | 0<<WGM12 | 0<<CS12 | 1<<CS11 | 0<<CS10;
  ICR1 = 20000; // period = 20ms
  TIMSK1 = 1<<ICIE1; // interrupt at TOP count
  // INT0 = left shaft encoder, INT1 = right shaft encoder
  EICRA = 0<<ISC11 | 1<<ISC10 | 0<<ISC01 | 1<<ISC00; // both edges
  EIMSK = 1<<INT1 | 1<<INT0; // enable external interrupts
}

void loop() {
  int left_offset, right_offset;
  left_offset = analogRead(0) - 512; // left offset
  right_offset = analogRead(1) - 512; // right offset
  OCR1A = 1500 + left_offset; // left servo
  OCR1B = 1500 + right_offset; // right servo
  delay(20);
}

// system heartbeat interrupt handler: 50 Hz

ISR(TIMER1_CAPT_vect) {
  static byte prescaler = 50;
  if(prescaler) {
    prescaler--; // decrement prescaler
  } else {
    prescaler = 50; // reset prescaler
    Serial.print("Odometer reports L=");
    Serial.print(left_odometer);
    Serial.print(", R=");
    Serial.println(right_odometer);
  }
}

// left shaft encoder interrupt

ISR(INT0_vect) {
  if(bit_is_clear(PIND, PIND2) ^ bit_is_clear(PIND, PIND4)) {
    left_odometer++; // anti-clockwise rotation
  } else {
    left_odometer--; // clockwise rotation
  }
}

// right shaft encoder interrupt

ISR(INT1_vect) {
  if(bit_is_clear(PIND, PIND3) ^ bit_is_clear(PIND, PIND7)) {
    right_odometer++; // anti-clockwise rotation
  } else {
    right_odometer--; // clockwise rotation
  }
}
