#include <Servo.h>

Servo leftServo;

#define leftBumper() (digitalRead(2) == LOW)
#define rightBumper() (digitalRead(3) == LOW)

void setup() {
  digitalWrite(2, HIGH); // left bumper pullup
  digitalWrite(3, HIGH); // right bumper pullup
  leftServo.attach(9); // left wheel
}

void servoVelocity(Servo servo, float velocity) {
  int pulseWidth; // in microseconds
  pulseWidth = velocity * 500; // +/- 500 microseconds from center position
  pulseWidth += 1500; // center position offset
  servo.writeMicroseconds(pulseWidth);
}

void loop() {
  static float leftVelocity = 0.0;
  if(leftBumper()) {
    leftVelocity += 0.01; // more anti-clockwise
  } else if(rightBumper()) {
    leftVelocity -= 0.01; // less anti-clockwise, or more clockwise
  }
  servoVelocity(leftServo, leftVelocity); // set velocity
  delay(20);
}
