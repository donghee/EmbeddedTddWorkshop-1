#define HIGH 0x1
#define LOW  0x0

#define true 0x1
#define false 0x0

#define INPUT 0x0
#define OUTPUT 0x1

int digitalRead(int pin);
unsigned long millis();
void delay(unsigned long millis);
void pinMode(int pin, int mode);
