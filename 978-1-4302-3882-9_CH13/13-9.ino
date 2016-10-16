void goForward() {
  servoVelocity(LEFT_SERVO_MOTOR, 1.0);
  servoVelocity(RIGHT_SERVO_MOTOR, -1.0);
}

void goBackward() {
  servoVelocity(LEFT_SERVO_MOTOR, -1.0);
  servoVelocity(RIGHT_SERVO_MOTOR, 1.0);
}

void allStop() {
  servoVelocity(LEFT_SERVO_MOTOR, 0.0);
  servoVelocity(RIGHT_SERVO_MOTOR, 0.0);
}

void loop() {
  if(leftBumper()) {
    goForward();
  } else if(rightBumper()) {
    goBackward();
  } else {
    allStop();
  }
  delay(20);
}
