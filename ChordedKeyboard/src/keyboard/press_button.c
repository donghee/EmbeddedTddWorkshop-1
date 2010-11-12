//#include <stdio.h>
#include "press_button.h"

void button_pressed() 
{
    led_on();
}

void button_unpressed()
{
    led_off();
}

int imp_loop_step()
{
    if (is_pressed()) {
        button_pressed();
    } else {
        button_unpressed();
    }
    return 0; //shd_stop==0
}

void start()
{
    int shd_stop=0;

    while(!shd_stop) {
        shd_stop=loop_step();
    }
}

int (*loop_step)()=imp_loop_step;

void (*led_on)();
void (*led_off)();
int (*is_pressed)();
