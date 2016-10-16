volatile unsigned int left_odometer = 0, right_odometer = 0; // in encoder ticks
volatile int left_velocity, right_velocity; // wheel velocities in encoder ticks per sample period
int left_wheel, right_wheel; // wheel velocity set points

void setup() {
  pinMode(9, OUTPUT); // left servo PWM output
  pinMode(10, OUTPUT); // right servo PWM output
  Serial.begin(115200);
  Serial.println("*** Robot initializing ***");
  // timer/counter1 is used for servo PWM (mode 8) and system heartbeat
  TCCR1A = 1<<COM1A1 | 0<<COM1A0 | 1<<COM1B1 | 0<<COM1B0 | 0<<WGM11 | 0<<WGM10;
  TCCR1B = 1<<WGM13 | 0<<WGM12 | 0<<CS12 | 1<<CS11 | 0<<CS10;
  OCR1A = 1500; // ideal servo null point in microseconds
  OCR1B = 1500; // ideal servo null point in microseconds
  ICR1 = 20000; // period = 20ms
  TIMSK1 = 1<<ICIE1; // interrupt at TOP count
  // INT0 = left shaft encoder, INT1 = right shaft encoder
  EICRA = 0<<ISC11 | 1<<ISC10 | 0<<ISC01 | 1<<ISC00; // both edges
  EIMSK = 1<<INT1 | 1<<INT0; // enable external interrupts
}

void loop() {
  left_wheel = 0; // stop
  right_wheel = 0; // stop
}

// system heartbeat interrupt handler: 50 Hz

ISR(TIMER1_CAPT_vect) {
  static byte prescaler = 50;
  static unsigned int previous_left_odometer, previous_right_odometer;
  int left_error, right_error;
  if(prescaler) {
    prescaler--; // decrement prescaler
  } else {
    prescaler = 50; // reset prescaler
    Serial.print("Power reports L=");
    Serial.print(OCR1A);
    Serial.print(", R=");
    Serial.println(OCR1B);
  }
  // calculate wheel velocities
  left_velocity = left_odometer - previous_left_odometer;
  right_velocity = right_odometer - previous_right_odometer;
  previous_left_odometer = left_odometer; // remember...
  previous_right_odometer = right_odometer; // ...for next time
  // calculate errors
  left_error = left_wheel - left_velocity; // set point - reading
  right_error = right_wheel - right_velocity;
  // adjust power settings
  OCR1A += left_error;
  OCR1B += right_error;
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
