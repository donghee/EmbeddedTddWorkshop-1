#include <WProgram.h>
#include <math.h>

extern "C" {
#include "../../ChordedKeyboard/tests/keyevent.h"
}

int ledPin =  13;    // LED connected to digital pin 13

boolean A;
int event;
byte firstA;
byte secondA;
int a;

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(5, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  //set_uncertain_count(100);

  //set_sampling_rate(s_rate);
  set_debounce_period(15);

}

int main(void) {

  init();
  setup();
  for (;;) {
	  digitalWrite(ledPin, HIGH);   // set the LED on
	  A = digitalRead(5);
	  if (A == LOW) {
		  key_step(ON);
		  digitalWrite(ledPin, LOW);
	  }
	  else {
		  key_step(OFF);
	  }
	  event = get_event();
	  if (event != NOEVT) Serial.print(event, DEC);
  } // end for
} // end main
