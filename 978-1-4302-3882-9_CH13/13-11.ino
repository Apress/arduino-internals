void move(float linearVelocity, float angularVelocity) {
  servoVelocity(LEFT_SERVO_MOTOR, angularVelocity + linearVelocity);
  servoVelocity(RIGHT_SERVO_MOTOR, angularVelocity - linearVelocity);
}

void loop() {
  if(leftBumper()) {
    if(rightBumper()) { // both bumpers engaged
      move(-0.1, 0.0); // straight back, slowly
    } else { // just the left one
      move(0.0, 0.1); // turn left/anti-clockwise
    }
  } else if(rightBumper()) {
    move(0.0, -0.1); // turn right/clockwise
  } else {
    move(0.1, 0.0); // straight ahead slow
  }
  delay(20);
}
