const byte row_pins[7] = { 2, 3, 4, 5, 6, 7, 8 };
const byte column_pins[5] = { 9, 10, 11, 12, 13 };

void leds_off() {

  byte i;
  
  // reset all row pins
  for(i = 0; i < 7; i++) {
    digitalWrite(row_pins[i], LOW); // turn off row pin
    pinMode(row_pins[i], INPUT); // make row pin high-impedance
  }
  
  // reset all column pins
  for(i = 0; i < 5; i++) {
    digitalWrite(column_pins[i], LOW); // turn off column pin
    pinMode(column_pins[i], INPUT); // make column pin high-impedance
  }
}

void one_led(byte row, byte column) {
  row--;
  column--;
  leds_off(); // turn off all the LEDs
  pinMode(row_pins[row], OUTPUT); // turn on row pin
  digitalWrite(row_pins[row], HIGH); // rows = anodes = high
  pinMode(column_pins[column], OUTPUT); // turn on column pin
  digitalWrite(column_pins[column], LOW); // columns = cathodes = low
}

void setup() {
}

void loop() {
  one_led(1, 1);
  delay(1000);
  leds_off();
  delay(1000);
}
