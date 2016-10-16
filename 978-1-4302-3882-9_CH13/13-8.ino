#define leftBumper() (digitalRead(2) == LOW)
#define rightBumper() (digitalRead(3) == LOW)

typedef struct {
  int nullOffset; // in microseconds
  float velocity; // -1.0 to +1.0
  int pulseWidth; // adjusted pulse width (1000us to 2000us)
} ServoMotor;

enum {
  LEFT_SERVO_MOTOR,
  RIGHT_SERVO_MOTOR,
  MAX_MOTOR
};

ServoMotor servos[MAX_MOTOR]; // 0=left, 1=right

#define leftServo servos[LEFT_SERVO_MOTOR]
#define rightServo servos[RIGHT_SERVO_MOTOR]

void servoCalibrate() {
  while(!leftBumper()) {
    leftServo.nullOffset = analogRead(0) - 512; // left offset
    rightServo.nullOffset = analogRead(1) - 512; // right offset
    OCR1A = 1500 + leftServo.nullOffset; // left servo
    OCR1B = 1500 + rightServo.nullOffset; // right servo
    delay(20);
  }
}

void servoVelocity(char servoIndex, float velocity) {
  if((servoIndex == LEFT_SERVO_MOTOR) || (servoIndex == RIGHT_SERVO_MOTOR)) {
    velocity = constrain(velocity, -1.0, +1.0); // constrain velocity parameter from -1.0 to +1.0
    servos[servoIndex].velocity = velocity; // save velocity parameter
    if(velocity == 0.0) {
      servos[servoIndex].pulseWidth = 0; // quit sending pulses
    } else {
      // translate normalized velocity to pulse width in microseconds
      servos[servoIndex].pulseWidth = velocity * 500; // +/- 500 microseconds variation
      servos[servoIndex].pulseWidth += 1500; // mid-point pulse width
      servos[servoIndex].pulseWidth += servos[servoIndex].nullOffset; // null adjust
      // constrain pulse width from 0 to 2500 microseconds
      servos[servoIndex].pulseWidth = constrain(servos[servoIndex].pulseWidth, 0, 2500);
    }
    switch(servoIndex) {
      case LEFT_SERVO_MOTOR:
        OCR1A = servos[servoIndex].pulseWidth;
        break;
      case RIGHT_SERVO_MOTOR:
        OCR1B = servos[servoIndex].pulseWidth;
        break;
    }
  }
}

void setup() {
  digitalWrite(2, HIGH); // left bumper switch pull up enable
  digitalWrite(3, HIGH); // right bumper switch pull up enable
  pinMode(9, OUTPUT); // PWM output for left wheel servo
  pinMode(10, OUTPUT); // PWM output for right wheel servo
  // initialize phase & frequency correct PWM outputs
  TCCR1A = 1<<COM1A1 | 0<<COM1A0 | 1<<COM1B1 | 0<<COM1B0 | 0<<WGM11 | 0<<WGM10;
  // timer clock = F_CPU/16, for 1us resolution
  TCCR1B = 1<<WGM13 | 0<<WGM12 | 0<<CS12 | 1<<CS11 | 0<<CS10;
  ICR1 = 20000; // period = 20ms
  servoCalibrate(); // calibrate those servos
}

void loop() {
  servoVelocity(LEFT_SERVO_MOTOR, 0.0);
  servoVelocity(RIGHT_SERVO_MOTOR, 0.0);
}
