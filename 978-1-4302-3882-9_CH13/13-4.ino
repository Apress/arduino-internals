#include <Servo.h>

Servo leftServo;

void setup() {
  digitalWrite(2, HIGH); // enable pullup
  digitalWrite(3, HIGH); // enable pullup
}

#define leftBumper() (digitalRead(2) == LOW)
#define rightBumper() (digitalRead(3) == LOW)

void leftServoClockwise() {
  leftServo.attach(9);
  leftServo.writeMicroseconds(1000); // clockwise
}

void leftServoAntiClockwise() {
  leftServo.attach(9);
  leftServo.writeMicroseconds(2000); // anti-clockwise
}

void leftServoStop() {
  leftServo.detach(); // stop
}

void loop() {
  if(leftBumper()) {
    leftServoClockwise();
  } else if(rightBumper()) {
    leftServoAntiClockwise();
  } else {
    leftServoStop();
  }
}
