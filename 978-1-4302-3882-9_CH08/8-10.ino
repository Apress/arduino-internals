volatile byte seconds_units = 0;
volatile byte seconds_tens = 0;
volatile byte minutes_units = 0;
volatile byte minutes_tens = 0;
volatile byte hours_units = 2;
volatile byte hours_tens = 1;

const byte numerals[10] = {
  ~0b00111111, // 0
  ~0b00000110, // 1
  ~0b01011011, // 2
  ~0b01001111, // 3
  ~0b01100110, // 4
  ~0b01101101, // 5
  ~0b01111101, // 6
  ~0b00000111, // 7
  ~0b01111111, // 8
  ~0b01101111, // 9
};

void setup() {

  // digit drivers - active low
  pinMode(2, OUTPUT); // digit 1 - right
  pinMode(3, OUTPUT); // digit 2
  pinMode(4, OUTPUT); // digit 3
  pinMode(5, OUTPUT); // digit 4 - left
  
  // segments - active low
  pinMode(6, OUTPUT); // segment a
  pinMode(7, OUTPUT); // segment b
  pinMode(8, OUTPUT); // segment c
  pinMode(9, OUTPUT); // segment d
  pinMode(10, OUTPUT); // segment e
  pinMode(11, OUTPUT); // segment f
  pinMode(12, OUTPUT); // segment g
  pinMode(13, OUTPUT); // segment DP, also Arduino LED

  // turn LEDs "off"
  digitalWrite(2, HIGH); // digit 1 off
  digitalWrite(3, HIGH); // digit 2 off
  digitalWrite(4, HIGH); // digit 3 off
  digitalWrite(5, HIGH); // digit 4 off
  
  // set up 1 second interrupt on Timer/counter1
  TCCR1A = 0;
  TCCR1B = 1<<WGM13 | 1<<WGM12 | 1<<CS12 | 1<<CS10; // clock = F_CPU / 1024 = 15625 Hz
  ICR1 = 15625;
  bitSet(TIMSK1, ICIE1); // enable capture event interrupt
  
  // set up ~240Hz interrupt on Timer/Counter2
  TCCR2A = 0;
  TCCR2B = 6; // select CK/256
  bitSet(TIMSK2, TOIE2); // enable overflow interrupt
}

void loop() {
  // nothing happens here!
}

void drawSegment(byte index) {
  digitalWrite(6, numerals[index] & 0x01); // segment a
  digitalWrite(7, numerals[index] & 0x02); // segment b
  digitalWrite(8, numerals[index] & 0x04); // segment c
  digitalWrite(9, numerals[index] & 0x08); // segment d
  digitalWrite(10, numerals[index] & 0x10); // segment e
  digitalWrite(11, numerals[index] & 0x20); // segment f
  digitalWrite(12, numerals[index] & 0x40); // segment g
}

ISR(TIMER1_CAPT_vect) {

  // keep time:  this interrupt should happen once every second
  
  seconds_units++; // count seconds x 1
  if(seconds_units > 9) {
    seconds_units = 0; // reset seconds x 1
    seconds_tens++; // count seconds x 10
    if(seconds_tens > 5) {
      seconds_tens = 0; // reset seconds x 10
      minutes_units++; // count minutes x 1
      if(minutes_units > 9) {
        minutes_units = 0; // reset minutes x 1
        minutes_tens++; // count minutes x 10
        if(minutes_tens > 5) {
          minutes_tens = 0; // reset minutes x 10
          hours_units++; // count hours x 1
          if(hours_units > 9) {
            hours_units = 0; // reset hours x 1
            hours_tens++; // count hours x 10
          }
          if((hours_units == 3) && (hours_tens == 1)) {
            hours_units = 1;
            hours_tens = 0;
          }
        }
      }
    }
  }
}

ISR(TIMER2_OVF_vect) {
  
  // tell time:  this interrupt should happen 240 times a second
  
  static byte digit = 0;
  
  // turn on the correct digit 0-3
  
  switch(digit) {
    case 0:
      digitalWrite(13, HIGH); // turn off decimal point
      digitalWrite(5, HIGH); // digit 4 off
      drawSegment(minutes_units);
      digitalWrite(2, LOW); // digit 1 on
      break;
    case 1:
      digitalWrite(13, LOW); // turn on decimal point
      digitalWrite(2, HIGH); // digit 1 off
      drawSegment(minutes_tens);
      digitalWrite(3, LOW); // digit 2 on
      break;
    case 2:
      digitalWrite(13, LOW); // turn on decimal point
      digitalWrite(3, HIGH); // digit 2 off
      drawSegment(hours_units);
      digitalWrite(4, LOW); // digit 3 on
      break;
    case 3:
      digitalWrite(13, HIGH); // turn off decimal point
      digitalWrite(4, HIGH); // digit 2 off
      drawSegment(hours_tens);
      digitalWrite(5, LOW); // digit 3 on
      break;
  }
  
  digit++; // move on to the next digit
  if(digit > 3) digit = 0; // roll over
}
