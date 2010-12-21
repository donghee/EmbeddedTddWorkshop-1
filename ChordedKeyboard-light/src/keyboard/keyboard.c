#include <WProgram.h>
#include "keyboard.h"

#define MAX_BUTTON 5

static int wakeup_time;
static int button_pins[MAX_BUTTON] = {1,2,3,4,5};
static int last_key_code;

static int button_to_pin(button) {
    int pin;
    pin = button_pins[button-1];
    return pin;
}
    
int is_pressed(int button) {
    int pin;
    pin = button_to_pin(button);
    return !digitalRead(pin);
}

int any_button_pressed() {
    last_key_code = read_all_buttons();    
    return last_key_code > 0 ? true : false;
}

int read_all_buttons() {
    int i;
    int code = 0;
    for (i = 0; i<MAX_BUTTON ; i++){
        if (is_pressed(i+1))
            code += ( 1 << i);
    }
    return code ;
}

void set_composite_wakeup(int time)
{
    wakeup_time = time;
}

void set_buttons_pin(int * btn) {
    int i;
    for (i=0 ; i< MAX_BUTTON; i++) {
        button_pins[i] = btn[i];
        pinMode(button_pins[i], INPUT);
    }

}

void wait_for_composite()
{
    //TODO: change wakeup_time to composite time
    int composite_time = wakeup_time;
    int key_code = read_all_buttons();
    while(last_key_code  < key_code) {
        last_key_code = key_code;
        delay(composite_time);
        composite_time = composite_time/2;
        key_code = read_all_buttons();
    }
}

void wait_for_debouncing()
{
    delay(wakeup_time);
}


int loop_keyboard_step() {
    static int key_code;
    if (any_button_pressed()) {
        wait_for_debouncing();
        wait_for_composite();
        key_code = read_all_buttons();
        send_serial(key_code);
        while(any_button_pressed()) {}
    }
    return 0;
}

void (*send_serial)(int);
