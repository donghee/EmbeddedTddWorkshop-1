#include "debounce.h"
#include "press_button.h"

int debounce_time;

void set_debounce_time(int millisecs) {
    debounce_time = millisecs;
}
int get_debounce_time() {
    return debounce_time;
}

int process_debouncing(int button_state) {
    static unsigned long wakeuptime=0;
    int next_btn_state=button_state;
    int deb_pres;
    unsigned long cmt=cmillis();

    if (button_state>=DEBOUNCING_OFF && cmt >=wakeuptime)
        next_btn_state=is_pressed();
    else if (button_state<DEBOUNCING_OFF &&
             (deb_pres=is_pressed()) !=button_state) {
        next_btn_state=DEBOUNCING_OFF+deb_pres;
        wakeuptime=cmt+get_debounce_time();
    } 
    return next_btn_state;
}

void (*_delay)(long unsigned);
unsigned long (*cmillis)();
