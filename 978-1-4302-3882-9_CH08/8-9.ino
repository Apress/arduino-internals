#define PUSH_BUTTON_INPUT 5

#define SEGMENT_A 6
#define SEGMENT_B 7
#define SEGMENT_C 8
#define SEGMENT_D 9
#define SEGMENT_E 10
#define SEGMENT_F 11
#define SEGMENT_G 12
#define SEGMENT_DP 13

void setup(void) {
  
  // push button input
  
  pinMode(PUSH_BUTTON_INPUT, INPUT); // this is an input
  digitalWrite(PUSH_BUTTON_INPUT, HIGH); // enable built-in pull-up resistor
  
  // turn off all LED outputs

  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, LOW);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, LOW);
  digitalWrite(SEGMENT_DP, LOW);
  
  // LED segments are all outputs
  
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);
  pinMode(SEGMENT_DP, OUTPUT);
}

// buttonPress() function returns TRUE if button is pressed, FALSE otherwise

#define TRUE 1
#define FALSE 0

int buttonPress(void) {
  
  if(digitalRead(PUSH_BUTTON_INPUT) == LOW) {
    return TRUE;
  } else {
    return FALSE;
  }
}

// LEDnumber() displays a single digit on the 7-segment LED display, 0-9

const byte LEDsegment[] = {
  // GFEDCBA
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

void LEDnumber(int number) {
  
  unsigned char i;
  
  if(number < 0) {
    for(i = SEGMENT_A; i <= SEGMENT_G; i++) digitalWrite(i, LOW); // turn off all segments
  } else {
  
    digitalWrite(SEGMENT_A, LEDsegment[number] & 0x01); // segment A
    digitalWrite(SEGMENT_B, LEDsegment[number] & 0x02); // segment B
    digitalWrite(SEGMENT_C, LEDsegment[number] & 0x04); // segment C
    digitalWrite(SEGMENT_D, LEDsegment[number] & 0x08); // segment D
    digitalWrite(SEGMENT_E, LEDsegment[number] & 0x10); // segment E
    digitalWrite(SEGMENT_F, LEDsegment[number] & 0x20); // segment F
    digitalWrite(SEGMENT_G, LEDsegment[number] & 0x40); // segment G
  }
}

#define DELAY_TIME 100 // 100 milliseconds = 0.1 seconds

void loop(void) {
  
  unsigned char x = 0;
  
  if(buttonPress()) {
    digitalWrite(SEGMENT_DP, HIGH); // turn on decimal point if button is pressed
  } else {
    digitalWrite(SEGMENT_DP, LOW); // else turn it off
  }
  
  LEDnumber(0); // display a 0
  delay(DELAY_TIME); // a short delay
  LEDnumber(1); // display a 1
  delay(DELAY_TIME); // a short delay
  LEDnumber(2); // display a 2
  delay(DELAY_TIME); // a short delay
  LEDnumber(3); // display a 3
  delay(DELAY_TIME); // a short delay
  LEDnumber(4); // display a 4
  delay(DELAY_TIME); // a short delay
  LEDnumber(5); // display a 5
  delay(DELAY_TIME); // a short delay
  LEDnumber(6); // display a 6
  delay(DELAY_TIME); // a short delay
  LEDnumber(7); // display a 7
  delay(DELAY_TIME); // a short delay
  LEDnumber(8); // display a 8
  delay(DELAY_TIME); // a short delay
  LEDnumber(9); // display a 9
  delay(DELAY_TIME); // a short delay
  
  LEDnumber(-1); // clear the LED display
  
  // now loop here forever & ever
  
  while(1) {
    
    while(buttonPress() == FALSE); // wait here for button to be pressed
    while(buttonPress() == TRUE); // wait here for button to be released

    LEDnumber(x);
    x++;
    if(x >= 10) x = 0; // start back over at zero
    delay(DELAY_TIME);
  }
}
