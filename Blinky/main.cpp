#include <WProgram.h>
#include <math.h>

int ledPin =  13;    // LED connected to digital pin 13

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(5, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

// the loop() method runs over and over again,
// as long as the Arduino has power

boolean A;
byte firstA;
byte secondA;

int main(void) {

  /* Must call init for arduino to work properly */
  init();
  setup();

  for (;;) {
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  A = digitalRead(5);
	  //	  A = 19.5 * log10((0.9*A) + 1);
	  Serial.print(A, BYTE);
  } // end for
} // end main
