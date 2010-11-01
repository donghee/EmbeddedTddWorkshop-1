#include <WProgram.h>
#include <math.h>

extern "C" {
#include "../ChordedKeyboard/include/press_button.h"
}

int ledPin =  13;
int buttonPin = 5;

void setup()   {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

int main(void) {

  init();
  setup();
  for (;;) {
      start();
      //	  digitalWrite(ledPin, HIGH);   // set the LED on
  } 
} 
