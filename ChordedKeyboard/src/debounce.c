#include "debounce.h"
#include "press_button.h"

int debounce_time;

void set_debounce_time(int millisecs) {
    debounce_time = millisecs;
}

int process_debouncing(int button_state) {
    if (is_pressed()!=button_state) {
        _delay(debounce_time);
        return is_pressed();
    }
    return button_state;
}

void (*_delay)(long unsigned);
