#include <avr/sleep.h>

extern volatile unsigned long timer0_millis;

void setup() {
  pinMode(13, OUTPUT); // an LED is attached to D13
}

void loop() {
  while(timer0_millis < 1000) {
    set_sleep_mode(SLEEP_MODE_IDLE); // select "lightly napping"
    sleep_mode(); // go to sleep
  }
  timer0_millis = 0; // reset millisecond counter
  bitSet(PINB, 5); // toggle LED
}
