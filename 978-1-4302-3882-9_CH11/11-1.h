// LED.h - Example library for manipulating LEDs - public domain

#ifndef LED_h
#define LED_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

class LED {
		byte _pin; // the pin number
		byte _state; // the state of the LED:  HIGH=on, LOW=off
	public:
		LED(byte pin); // the constructor
		void on(); // turn the LED on
		void off(); // turn the LED off
		void toggle(); // toggle the LED
		byte state(); // return the current state of the LED
};

#endif
