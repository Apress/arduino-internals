#include <IRremote.h>

IRsend irsend;

void setup() {
}

void loop() {
  irsend.sendNEC(0xFFB04F, 32); // on
  delay(1000);
  irsend.sendNEC(0xFFF807, 32); // off
  delay(1000);
}
