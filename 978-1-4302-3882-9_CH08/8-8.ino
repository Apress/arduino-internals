const byte row_pins[7] = { 2, 3, 4, 5, 6, 7, 8 };
const byte column_pins[5] = { 9, 10, 11, 12, 13 };

void setup() {
  
  byte i;
  
  for(i = 0; i < 7; i++) {
    digitalWrite(row_pins[i], LOW);
    pinMode(row_pins[i], OUTPUT);
  }
  
  for(i = 0; i < 5; i++) {
    digitalWrite(column_pins[i], LOW);
    pinMode(column_pins[i], OUTPUT);
  }
}

void draw_column(byte bits) {
  
  digitalWrite(row_pins[0], bits & 0x40 ? LOW : HIGH);
  digitalWrite(row_pins[1], bits & 0x20 ? LOW : HIGH);
  digitalWrite(row_pins[2], bits & 0x10 ? LOW : HIGH);
  digitalWrite(row_pins[3], bits & 0x08 ? LOW : HIGH);
  digitalWrite(row_pins[4], bits & 0x04 ? LOW : HIGH);
  digitalWrite(row_pins[5], bits & 0x02 ? LOW : HIGH);
  digitalWrite(row_pins[6], bits & 0x01 ? LOW : HIGH);
}

const byte bitmap[5] = {
  0b00011111,
  0b00100100,
  0b01000100,
  0b00100100,
  0b00011111
};

void loop() {
  
  byte column;
  
  for(column = 0; column < 5; column++) {

    digitalWrite(column_pins[column], HIGH); // enable this column
    draw_column(bitmap[column]);
    delay(2);
    digitalWrite(column_pins[column], LOW); // disable this column
  }
}
