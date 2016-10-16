#include <LED.h>

LED led(13); // assign digital pin 13 to an LED

void setup() {
}

void loop() {
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
