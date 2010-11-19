#include <WProgram.h>

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

void imp_delay(long unsigned millisecs) {
    delay(millisecs);
}

unsigned long imp_cmillis() {
    return millis();
}

void (*_delay)(long unsigned)=imp_delay;
void (*led_on)()=imp_led_on;
void (*led_off)()=imp_led_off;
int (*is_pressed)()=imp_is_pressed;
unsigned long (*cmillis)()=imp_cmillis;

