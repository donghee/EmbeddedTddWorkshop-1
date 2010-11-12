#include "event.h"
#include "debounce.h"

int p_button_state=BUTTON_OFF;

int get_event() {
    int button_state;
    int event = NOEVT;

    while (event == NOEVT) {
        button_state = process_debouncing(p_button_state);
        if (p_button_state==DEBOUNCING_ON && button_state==BUTTON_ON)
            event = PRESSED;
        else if (p_button_state==DEBOUNCING_OFF && button_state==BUTTON_OFF)
            event = RELEASE;
        else
            event = NOEVT;
        p_button_state = button_state;
    }
    return event;
}







