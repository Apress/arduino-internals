#include <Servo.h>

Servo leftServo, rightServo;

int leftServoNull, rightServoNull;

#define leftBumper() (digitalRead(2) == LOW)
#define rightBumper() (digitalRead(3) == LOW)

void servoNullCalibration() {
  while(!leftBumper()) {
    leftServoNull = analogRead(0) - 512;
    rightServoNull = analogRead(1) - 512;
    leftServo.writeMicroseconds(1500 + leftServoNull);
    rightServo.writeMicroseconds(1500 + rightServoNull);
    delay(20);
  }
}

void setup() {
  digitalWrite(2, HIGH); // left bumper pullup
  digitalWrite(3, HIGH); // right bumper pullup
  leftServo.attach(9); // left wheel
  rightServo.attach(10); // right wheel
  servoNullCalibration(); // calibrate those servos
}

void servoVelocity(Servo servo, float velocity, int nullOffset) {
  int pulseWidth; // in microseconds
  pulseWidth = velocity * 500; // +/- 500 microseconds from center position
  pulseWidth += 1500; // center position offset
  pulseWidth += nullOffset;
  servo.writeMicroseconds(pulseWidth);
}

void loop() {
  static float leftVelocity = 0.0;
  if(leftBumper()) {
    leftVelocity += 0.01; // more clockwise
  } else if(rightBumper()) {
    leftVelocity -= 0.01; // less clockwise
  }
  servoVelocity(leftServo, leftVelocity, leftServoNull); // set velocity
  delay(20);
}
