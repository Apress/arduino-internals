#define KEYS 8

volatile byte previous_state[KEYS];
volatile byte state[KEYS];
volatile byte changes[KEYS];
const byte key_pins[KEYS] = { 5, 6, 7, 8, 9, 10, 11, 12 };
const byte notes[KEYS] = { 60, 62, 64, 65, 67, 69, 71, 72 }; // middle C and up

void setup() {
  for(byte i = 0; i < KEYS; i++) digitalWrite(key_pins[i], HIGH); // pullups on!
  Serial.begin(31250); // MIDI special baud rate
  TCCR2B = 0<<WGM22 | 1<<CS22 | 1<<CS21 | 1<<CS20; // CK/1024
  TIMSK2 = 1<<TOIE2; // enable overflow interrupt
}

void loop() {
  
  byte i;
  
  for(i = 0; i < KEYS; i++) {
    if(changes[i]) {
      Serial.write(state[i] ? 0x90 : 0x80); // Note On or Note Off, channel 1
      Serial.write(notes[i]); // the MIDI note number
      Serial.write(0x64); // medium velocity
      changes[i] = 0; // done!
    }
  }
}

ISR(TIMER2_OVF_vect) {
  byte i;
  // scan the buttons
  for(i = 0; i < KEYS; i++) {
    previous_state[i] = state[i]; // save previous state
    state[i] = digitalRead(key_pins[i]) ? 0 : 1; // record present state
    changes[i] = state[i] ^ previous_state[i]; // any changes?
  }
}
