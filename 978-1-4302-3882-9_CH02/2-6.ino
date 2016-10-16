#define LED 13

void setup() {
	pinMode(LED, OUTPUT); // D13 is now an output
}

void loop() {
	digitalWrite(LED, HIGH); // turn on the LED
	delay(1000); // one-second delay
	digitalWrite(LED, LOW); // turn off the LED
	delay(1000); // another one-second delay
}
