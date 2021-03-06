#include <WProgram.h>

extern "C" {
#include "debounce.h"
#include "event.h"    
}

#define DEBOUNCE_DELAY 20

int ledPin =  13;
int buttonPin = 5;
int button_event = NOEVT;

void setup() {
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    set_debounce_time(DEBOUNCE_DELAY);
    Serial.begin(38400);
}

int main(void) {
    init();
    setup();
    loop();
}

void loop() {
    while(1) {
        button_event = get_event();
        Serial.print(button_event,DEC);
    }
}
