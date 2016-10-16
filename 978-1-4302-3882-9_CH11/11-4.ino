#include <LED.h>

LED led(13); // assign digital pin 13 to an LED

void setup() {
}

void loop() {
  led.toggle();
  if(led.state()) {
    delay(1000);
  } else {
    delay(250);
  }
}
