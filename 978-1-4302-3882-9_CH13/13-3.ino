#include <Servo.h>

Servo leftServo;

void setup() {
  digitalWrite(2, HIGH); // enable pullup on left bumper switch
  digitalWrite(3, HIGH); // enable pullup on right bumper switch
}

void loop() {
  leftServo.attach(9); // left wheel
  if(digitalRead(2) == LOW) {
    leftServo.writeMicroseconds(1000); // clockwise
  } else if(digitalRead(3) == LOW) {
    leftServo.writeMicroseconds(2000); // anti-clockwise
  } else {
    leftServo.detach(); // stop
  }
}
