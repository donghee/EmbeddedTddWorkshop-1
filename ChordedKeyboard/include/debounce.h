extern void set_debounce_time(int millisecs);
extern int process_debouncing(int state);

// TODO: move below function point to time.c
extern void (*_delay)(long unsigned millisecs);
extern unsigned long (*cmillis)();

#define BUTTON_OFF 0
#define BUTTON_ON 1

#define DEBOUNCING_OFF 2
#define DEBOUNCING_ON 3
