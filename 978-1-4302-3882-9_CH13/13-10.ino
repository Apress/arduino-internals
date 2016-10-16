void straightLine(float velocity) {
  servoVelocity(LEFT_SERVO_MOTOR, velocity);
  servoVelocity(RIGHT_SERVO_MOTOR, -velocity);
}

void loop() {
  if(leftBumper()) {
    straightLine(0.1); // slow ahead
  } else if(rightBumper()) {
    straightLine(-0.1); // slow reverse
  } else {
    straightLine(0.0); // stop
  }
  delay(20);
}
