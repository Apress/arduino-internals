void setup() {
  Serial.begin(9600); // initialize serial port to 9600 bps
  Serial.println("Arduino performance test begins now.");
}

extern volatile unsigned long timer0_millis;

void loop() {

  unsigned long i = 0; // test value
  unsigned long stop_time; // in milliseconds
  
  // calculate stop time (current time + 1 second)
  stop_time = millis() + 1000;
  
  while(timer0_millis < stop_time) i++; // count!

  // report performance results:
  // number of loop iterations in one second
  Serial.print(i);
  Serial.println(" loops in one second.");

  while(1); // and stop here  
}
