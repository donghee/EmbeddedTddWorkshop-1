#include <WProgram.h>

void imp_send_serial(int code) {
    if(code)
        Serial.print(code,BYTE);
}

void (*send_serial)(int) = imp_send_serial;

