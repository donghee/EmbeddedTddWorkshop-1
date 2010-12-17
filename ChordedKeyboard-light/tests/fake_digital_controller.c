#include "fake_digital_controller.h"

#define MAX_PINS 13
static int digital_pin_values[MAX_PINS];
static unsigned long _ctime;

void digitalPinSetting() {
    int i;
    for (i =0; i < 13; i++) {
        digital_pin_values[i] = LOW;
    }
}

void fake_digitalWrite(int pin, int value) {
    digital_pin_values[pin-1] = value;
}

int digitalRead(int pin) {
    return digital_pin_values[pin-1];
}

void delay(unsigned long millis) {
    _ctime += millis;
}

void pinMode(int pin, int mode) {
}

void fake_set_ctime(unsigned long ctime) {
    _ctime = ctime;
}

unsigned long get_ctime() {
    return _ctime;
}
