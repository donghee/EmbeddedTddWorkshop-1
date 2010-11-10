#include <WProgram.h>

extern "C" {
#include "../ChordedKeyboard/include/press_button.h"
#include "../ChordedKeyboard/include/debounce.h"
}

#define PRESSED 1
#define RELEASE 2
#define NOEVT 0
#define DEBOUNCE_DELAY 2

int ledPin =  13;
int buttonPin = 5;
int button_state = BUTTON_OFF;
int p_button_state;

void setup()   {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  set_debounce_time(DEBOUNCE_DELAY);
  p_button_state = button_state;
  Serial.begin(38400);
}

int main(void) {
  init();
  setup();
  //  start(); //TODO: change name to loop
  loop();
}

void loop() {
    while(1) {
        button_state = process_debouncing(p_button_state);
        if  (!p_button_state && button_state) {
            Serial.print(PRESSED,DEC);
            // led_on();            
        }else if (p_button_state && !button_state) {
            Serial.print(RELEASE,DEC);
            // led_off();
        }else {
            // Serial.print(NOEVT,DEC);
        }
        p_button_state = button_state;
    }
}
