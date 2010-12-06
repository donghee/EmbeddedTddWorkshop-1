#include "event.h"
#include "debounce.h"
#include "press_button.h"

int p_button_state=BUTTON_OFF;
//int[] p_button_states= { BUTTON_OFF, BUTTON_OFF}

int current_states[5] = {ST_BUTTON_RELEASED, ST_BUTTON_RELEASED,
                         ST_BUTTON_RELEASED, ST_BUTTON_RELEASED,
                         ST_BUTTON_RELEASED};


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


void set_current_state(int state)
{
    set_current_state2(0, state);
}

void set_current_state2(int button, int state)
{
    current_states[button] = state;
}

void occur2(int button, int event)
{
    int current_state = get_current_state2(button);
    set_current_state2(button, current_state+1);

    if (event == EV_WAKE_UP) {
        if (is_pressed(button)) 
            set_current_state2(button, ST_BUTTON_PRESSED);
        else
            set_current_state2(button, ST_BUTTON_RELEASED);
    }
}

void occur(int event) 
{
    occur2(0,event);
}


int get_current_state() 
{
    return get_current_state2(0);
}

int get_current_state2(int button) 
{
    return current_states[button];
}
