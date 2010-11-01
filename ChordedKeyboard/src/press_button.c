//#include <stdio.h>
#include "press_button.h"
#include "WProgram.h"

int imp_is_pressed()
{
    return !digitalRead(5);
    //TODO: check real pin
}

void imp_led_on()
{
    digitalWrite(13, HIGH);    
    //TODO: put real pin setting code
}

void imp_led_off()
{
    digitalWrite(13, LOW);        
    //TODO: put real pin setting code
}

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

void (*led_on)()=imp_led_on;
void (*led_off)()=imp_led_off;
int (*loop_step)()=imp_loop_step;
int (*is_pressed)()=imp_is_pressed;
//void (*_button_pressed)()=imp_button_pressed;
