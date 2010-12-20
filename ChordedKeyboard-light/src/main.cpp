#include <WProgram.h>

extern "C" {
#include "keyboard.h"
}

int ledPin =  13;
int buttonPin = 5;
int buttonPins[5] = {2,3,5,6,7};

void setup() {
    pinMode(ledPin, OUTPUT);
    set_buttons_pin(buttonPins);
    set_composite_wakeup(70);
    Serial.begin(38400);
}

int main(void) {
    init();
    setup();
    loop();
}

void loop() {
    int shd_stop = 0;
    while(!shd_stop) {
        shd_stop = loop_keyboard_step();
        //        Serial.print(1,DEC);
    }
}
