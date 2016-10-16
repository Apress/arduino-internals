#define Kp 25 // proportional factor
#define Ki 0.1 // integral factor
#define Kd 0.5 // derivative factor

volatile unsigned int left_odometer = 0, right_odometer = 0; // in encoder ticks
volatile int left_velocity, right_velocity; // wheel velocities in encoder ticks per sample period
int left_wheel, right_wheel; // wheel velocity set points
float left_wheel_power, right_wheel_power; // -1.0 to +1.0

unsigned int servoPower(float power) {
  int pulse_width = 1500;
  power = constrain(power, -1.0, +1.0); // limits
  pulse_width += power * 500; // +/-500 microseconds
  return pulse_width;
}

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
  int set_point;
  
  for(set_point = -5; set_point < 6; set_point++) {
    Serial.print("Set point = ");
    Serial.println(set_point);
    left_wheel = set_point;
    right_wheel = set_point;
    delay(2500);
  }
}

// system heartbeat interrupt handler: 50 Hz

ISR(TIMER1_CAPT_vect) {
  static byte prescaler = 50;
  static unsigned int previous_left_odometer, previous_right_odometer;
  int left_error, right_error;
  int left_proportional_error, right_proportional_error;
  static int left_integral_error, right_integral_error;
  int left_derivative_error, right_derivative_error;
  static int left_previous_error, right_previous_error;
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
  right_error = right_wheel - right_velocity; // set point - reading
  left_proportional_error = left_error * Kp;
  right_proportional_error = right_error * Kp;
  left_integral_error += (left_error * Ki); // integrate
  right_integral_error += (right_error * Ki); // integrate
  left_derivative_error = (left_previous_error * Kd); // from last time
  right_derivative_error = (right_previous_error * Kd); // from last time
  left_error = left_proportional_error + left_integral_error - left_derivative_error;
  right_error = right_proportional_error + right_integral_error - right_derivative_error;
  // adjust power settings
  left_wheel_power += (left_error / 1000.0); // scale
  right_wheel_power += (right_error / 1000.0); // scale
  OCR1A = servoPower(left_wheel_power);
  OCR1B = servoPower(right_wheel_power);
  left_previous_error = left_error; // remember...
  right_previous_error = right_error; // ...for next time
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
