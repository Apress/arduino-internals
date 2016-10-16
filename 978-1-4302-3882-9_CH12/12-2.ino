void setup() {
  Serial.begin(9600);  // serial monitor
  Serial3.begin(115200); // from PC
  digitalWrite(15, HIGH); // turn on pullup resistor on RX3/D15 * required
}

void loop() {
  if(Serial3.available()) {
    Serial.write(Serial3.read());
  }
}
