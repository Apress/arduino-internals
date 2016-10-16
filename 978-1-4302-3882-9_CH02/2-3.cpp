void setup(void); // setup() function prototype
void loop(void); // loop() function prototype

int main(void) {

	setup(); // perform whatever one-time initializations that are required

	while(1) {
		loop(); // repeat this over and over again
	}

	return 0; // this never happens
}
