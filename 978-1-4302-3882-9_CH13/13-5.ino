#include <Servo.h>

Servo leftServo;

void setup() {
  digitalWrite(2, HIGH); // enable pullup
  digitalWrite(3, HIGH); // enable pullup
}

#define leftBumper() (digitalRead(2) == LOW)
#define rightBumper() (digitalRead(3) == LOW)

#define leftServoClockwise() leftServoVelocity(1)
#define leftServoAntiClockwise() leftServoVelocity(-1)
#define leftServoStop() leftServoVelocity(0)

void leftServoVelocity(signed char velocity) {
  switch (velocity) {
    case 1: // clockwise
      leftServo.attach(9);
      leftServo.writeMicroseconds(1000); // clockwise
      break;
    case 0: // stop
      leftServo.detach(); // stop
      break;
    case -1: // anti-clockwise
      leftServo.attach(9);
      leftServo.writeMicroseconds(2000); // anti-clockwise
      break;
  }
}

void loop() {
  if(leftBumper()) {
    leftServoVelocity(1); // clockwise
  } else if(rightBumper()) {
    leftServoVelocity(-1); // anti-clockwise
  } else {
    leftServoVelocity(0); // stop
  }
}
