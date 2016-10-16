void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Voltmeter");
}

#define SAMPLES 2500

void loop() {
  
  unsigned long voltage = 0;
  unsigned int i;
  
  for(i = 0; i < SAMPLES; i++) {
    voltage += analogRead(0); // accumulate samples
  }
  Serial.print((((voltage * 5.0) / 1024) / SAMPLES), 4);
  Serial.println("V");
}
