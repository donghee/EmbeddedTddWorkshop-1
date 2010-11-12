#include <WProgram.h>

extern "C" {
#include "../ChordedKeyboard/include/debounce.h"
#include "../ChordedKeyboard/include/event.h"    
}

#define DEBOUNCE_DELAY 20

int ledPin =  13;
int buttonPin = 5;
int button_event = NOEVT;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  set_debounce_time(DEBOUNCE_DELAY);
  Serial.begin(9600);
}

int main(void) {
  init();
  setup();
  loop();
}

void loop() {
    while(1) {
        button_event = get_event();
        if (button_event != NOEVT) 
            Serial.print(button_event,DEC);
    }
}
