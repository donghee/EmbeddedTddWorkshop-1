int is_pressed(int pin);
int read_all_buttons
();

enum {BUTTON_ON = 1, BUTTON_OFF = 0}; 

void set_composite_wakeup(int time);
void delay_for_composite();

int any_button_pressed();

extern void (*send_serial)(int code);

int loop_keyboard_step();


void set_buttons_pin(int* btns);
