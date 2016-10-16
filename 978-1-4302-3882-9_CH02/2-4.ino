#include <stdio.h>

int serial_console_putc(char c, FILE *) {
	Serial.write(c); // send a single character out via the serial port
	return 0; // indicate success
}

void setup() {
	Serial.begin(9600); // initialize the serial port
	fdevopen(&serial_console_putc, NULL); // point STDOUT to serial port
	printf("Hello, world!\n");
}

void loop() {
}
