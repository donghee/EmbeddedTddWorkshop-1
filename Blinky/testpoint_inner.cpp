#include <WProgram.h>
#include <math.h>

extern "C" {
#include "../../ChordedKeyboard/tests/keyevent.h"
}

#define BUF_SIZE 700

int ledPin =  13;    // LED connected to digital pin 13

boolean A;
int event;
int event_calls;

byte firstA;
byte secondA;
int i=0;


char buffer[BUF_SIZE];

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(5, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(1200);
  set_uncertain_count(200);
  digitalWrite(ledPin, HIGH);   // set the LED on
}

void printBuffer(){
  for (i=0; i< BUF_SIZE ;i++) {
	  //Serial.print(1,DEC);
	  Serial.print(buffer[i], DEC);
  }
}

int main(void) {
    unsigned long ctime=0;
    int k=0;

  init();
  setup();
  // for (int h=0;h<10;h++) {
  //     ctime=micros();
  //     Serial.println(1,DEC);
  //     Serial.println(micros()-ctime,DEC);
  // }

  for (;;k++) {
	  A = digitalRead(5);
      /*
      if (A==prev_A) {
          run_length++;
      } else {
          buffer.append(A,run_length);
          run_length=0;
      }
      */

	  if (A == LOW) {
		  key_step(ON);
	  }
	  else {
		  key_step(OFF);
	  }
	  event = get_event();
	  if (event != NOEVT) Serial.print(event, DEC);
      //Serial.println(event,DEC);

      // if (!(k%1000)) {
      //     k=0;
      //     Serial.println(micros()-ctime,DEC);
      //     ctime=micros();
      // }
          
  }
      /*
	  buffer[i] = event;
	  i++;
	  buffer[i] = A;
	  i++;

	  if (event == RELEASED) {
		  event_calls += 1;
		  if(event_calls == 4) {
			  printBuffer();
			  event_calls = 0;
		  }
	  }

	  if (i >= BUF_SIZE) {
		i=0;
	  }
	  */

} // end main
