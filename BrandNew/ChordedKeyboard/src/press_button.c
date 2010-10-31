#include <stdio.h>
#include "press_button.h"

int imp_is_pressed()
{
    printf("IMP: is pressed");
    //TODO: check real pin value
    return 0;
}

void imp_led_on()
{
    printf("IMP: turn led on");
    //TODO: put real pin setting code
}

void imp_led_off()
{
    printf("IMP: turn led off");
    //TODO: put real pin setting code
}

void _button_pressed() 
{
    led_on();
}

void _button_unpressed()
{
    led_off();
}

int imp_loop_step()
{
    if (is_pressed()) {
        _button_pressed();
    } else {
        _button_unpressed();
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

void (*led_on)()=imp_led_on;
void (*led_off)()=imp_led_off;
int (*loop_step)()=imp_loop_step;
int (*is_pressed)()=imp_is_pressed;
//void (*_button_pressed)()=imp_button_pressed;
