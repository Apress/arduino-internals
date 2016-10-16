#include <Servo.h>

Servo leftServo, rightServo;

void setup() {
  leftServo.attach(9); // D9 is connected to the left servo
  rightServo.attach(10); // D10 is connected to the right servo
  leftServo.writeMicroseconds(1500); // centering pulse
  rightServo.writeMicroseconds(1500); // centering pulse
}

void loop() {
}
