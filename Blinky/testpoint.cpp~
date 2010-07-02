#include <WProgram.h>
#include <math.h>

int ledPin =  13;    // LED connected to digital pin 13

boolean A;

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(5, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

int main(void) {

  init();
  setup();
  for (;;) {
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  A = digitalRead(5);
	  Serial.print(A, BYTE);
  } // end for
} // end main
