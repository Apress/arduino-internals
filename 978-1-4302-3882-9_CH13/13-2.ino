#include <Servo.h>

Servo leftServo, rightServo;

void setup() {
  leftServo.attach(9); // pin D9 is connected to the left servo
  rightServo.attach(10); // pin D10 is connected to the right servo
}

void loop() {
  int leftAdjust, rightAdjust;
  
  leftAdjust = analogRead(0); // read left servo adjust
  rightAdjust = analogRead(1); // read right servo adjust
  
  leftServo.writeMicroseconds(leftAdjust + 1500 - 512);
  rightServo.writeMicroseconds(rightAdjust + 1500 - 512);
  
  delay(20);
}
