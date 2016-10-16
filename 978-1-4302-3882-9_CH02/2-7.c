#include <avr/io.h>

int main(void) {

	long i;

	DDRB = 1<<5; // PB5/D13 is an output

	while(1) {
		PORTB = 1<<5; // LED is on
		for(i = 0; i < 100000; i++); // delay
		PORTB = 0<<5; // LED is off
		for(i = 0; i < 100000; i++); // delay
	}
}
