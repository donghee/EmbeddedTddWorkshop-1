extern void start();
extern void button_pressed();
extern void (*led_on)();
extern void (*led_off)();
extern int (*loop_step)();
extern int (*is_pressed)(int button);

extern void (*_delay)(unsigned long);

extern void start2();
extern void set_composite_wakeup(int time);
extern int read_all_buttons();
