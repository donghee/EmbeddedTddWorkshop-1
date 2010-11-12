extern void set_debounce_time(int millisecs);
extern int process_debouncing(int state);

extern void (*_delay)(long unsigned millisecs);

#define BUTTON_ON 1
#define BUTTON_OFF 0
