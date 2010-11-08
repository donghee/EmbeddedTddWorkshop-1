#include "event.h"
#include "debounce.h"

int p_button_state=BUTTON_OFF;

int get_event() {
    int button_state;
    int event;
    button_state = process_debouncing(p_button_state);
    if (!p_button_state && button_state)
        event = PRESSED;
    else if (p_button_state && !button_state)
        event = RELEASE;
    else
        event = NOEVT;
    p_button_state = button_state;
    return event;
}






