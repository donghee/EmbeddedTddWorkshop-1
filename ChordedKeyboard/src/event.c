#include "event.h"
#include "debounce.h"

int p_button_state = BUTTON_OFF;


int get_event() {
    int button_state;
    button_state = _process_debouncing(p_button_state);
    return PRESSED;
}

int (*_process_debouncing)(int);




