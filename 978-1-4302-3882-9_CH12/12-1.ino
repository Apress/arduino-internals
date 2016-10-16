void setup() {
  // pin directions
  pinMode(11, OUTPUT); // LED on PWM pin D11
  pinMode(5, INPUT); // D5 = button 1 (up)
  pinMode(6, INPUT); // D6 = button 2 (bright)
  pinMode(7, INPUT); // D7 = button 3 (dim)
  pinMode(8, INPUT); // D8 = button 4 (off)
  // initial settings
  analogWrite(11, 0); // LED off
  digitalWrite(5, HIGH); // enable pullup
  digitalWrite(6, HIGH); // enable pullup
  digitalWrite(7, HIGH); // enable pullup
  digitalWrite(8, HIGH); // enable pullup
  // serial port
  Serial.begin(9600);
  Serial.write(byte(0)); // turn off all the other LEDs
}

void loop() {
  
  static int brightness = 0; // the brightness of the LED: 0=off, 255=on
  static int previous_brightness = 0; // the previous brightness
  
  previous_brightness = brightness; // remember for later

  // check buttons  
  if(digitalRead(5) == LOW) brightness = 255; // full on
  if(digitalRead(6) == LOW) brightness++; // brighter
  if(digitalRead(7) == LOW) brightness--; // dimmer
  if(digitalRead(8) == LOW) brightness = 0; // off
  
  if(brightness < 0) brightness = 0; // lower limit
  if(brightness > 255) brightness = 255; // upper limit
  
  if(brightness != previous_brightness) {
    // the brightness has changed  
    Serial.write(brightness); // broadcast the new brightness
  }

  // any news from the network?
  if(Serial.available()) {
    brightness = Serial.read(); // fetch new brightness level
  }
 
  analogWrite(11, brightness); // update LED
  delay(10); // a short delay
}
