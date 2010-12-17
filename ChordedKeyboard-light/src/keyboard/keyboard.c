#include <WProgram.h>
#include "keyboard.h"
#define MAX_BUTTON 5

static int wakeup_time;
static int button_pins[MAX_BUTTON] = {1,2,3,4,5};

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

int real_all_buttons() {
    int i;
    int code = 0;
    for (i = 0; i<MAX_BUTTON ; i++){
        if (is_pressed(i+1))
            code += ( 1 << i);
    }
    return code ;
}

void set_composite_wakeup1(int time)
{
    wakeup_time = time;
}

void set_buttons_pin(int btn1, int btn2, int btn3, int btn4, int btn5)
{
    int i;
    button_pins[0] = btn1;
    button_pins[1] = btn2;
    button_pins[2] = btn3;
    button_pins[3] = btn4;
    button_pins[4] = btn5;
    
    for (i=0 ; i< MAX_BUTTON; i++) {
        pinMode(button_pins[i], INPUT);
    }
}

void delay_for_composite()
{
    delay(wakeup_time);
}

int any_button_pressed() {
    int i;
    for (i=0; i< MAX_BUTTON; i++) {
        if (is_pressed(i+1))
            return 1;
    }
    return 0;
}

int loop_keyboard_step() {
    static int code;
    if (any_button_pressed()) {
        delay_for_composite();
        code = real_all_buttons();
        send_serial(code);
        while(any_button_pressed()) {}
    }
    return 0;
}

void (*send_serial)(int);
