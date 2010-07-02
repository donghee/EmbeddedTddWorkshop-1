#include <WProgram.h>
#include <math.h>

extern "C" {
#include "../../ChordedKeyboard/tests/keyevent.h"
}

#define BUF_SIZE 500

int ledPin =  13;    // LED connected to digital pin 13

boolean A;
int event;
byte firstA;
byte secondA;
int i=0;

char buffer[BUF_SIZE];

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(5, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  set_uncertain_count(100);
}

void printBuffer(){
  for (i=0; i< BUF_SIZE ;i++) {
	Serial.print(1,DEC);	
	//	Serial.print(buffer[i], DEC);
  }
}

int main(void) {

  init();
  setup();
  for (;;) {
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  A = digitalRead(5);
	  if (A == LOW) {
		  key_step(ON);
	  }
	  else {
		  key_step(OFF);
	  }
	  event = get_event();
	  //	  if (event != NOEVT) Serial.print(event, DEC);

	  buffer[i] = A;
	  i++;

	  if (event == RELEASED) {
		printBuffer();
	  }

	  if (i >= BUF_SIZE) {
		i=0;
	  }


  } // end for
} // end main
