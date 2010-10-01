#define ON 1
#define OFF 0

#define NOEVT 0
#define PRESSED 1
#define RELEASED 2

extern void (*keydown_event_cb)(void);
extern int keydown_event;

//extern int ctime;
extern unsigned long last_debounce_time;
extern int debounce_period;

void set_key_state(int state);

void set_key_state1(int state);

int read_key_state();
int read_keydown_event();

void set_uncertain_count(int count);
void process_key_chattering();
void process_key_chattering1();

void key_step(int state);
int get_event();

void set_debounce_period(int delay);
void set_sampling_rate(int millis);
void set_key(int state);
void process_debouncing();
int read_key();
