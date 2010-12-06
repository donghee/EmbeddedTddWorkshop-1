//#include <stdio.h>
#include "press_button.h"

int wakeup;
/* int buttons[5] = [0,0,0,0,0]; */


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
    if (is_pressed(0)) {
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

void start2() 
{
    is_pressed(0);
    _delay(100);
}


int read_all_buttons() 
{
    int button_code=0;
    int i;
    for (i=0; i<5 ; i++) {
        button_code += (is_pressed(i)<<i);
    }

    return button_code;
    
}


void set_composite_wakeup(int time)
{
    wakeup = time;
}


    

int (*loop_step)()=imp_loop_step;

void (*led_on)();
void (*led_off)();
int (*is_pressed)(int button);
