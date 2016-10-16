ISR(TIMER1_CAPT_vect) {
  static byte prescaler = 50;
  static unsigned int previous_left_odometer, previous_right_odometer;
  if(prescaler) {
    prescaler--; // decrement prescaler
  } else {
    prescaler = 50; // reset prescaler
    Serial.print("Velocity reports L=");
    Serial.print(left_velocity);
    Serial.print(", R=");
    Serial.println(right_velocity);
  }
  // calculate wheel velocities
  left_velocity = left_odometer - previous_left_odometer;
  right_velocity = right_odometer - previous_right_odometer;
  previous_left_odometer = left_odometer; // remember...
  previous_right_odometer = right_odometer; // ...for next time
}
