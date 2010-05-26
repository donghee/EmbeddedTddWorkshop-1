#define ON 1
#define OFF 0

#define PRESSED 1
#define RELEASED 2

extern int keydown_event_count;
extern int keydown_event_counts[];
extern void (*keydown_event_cb)(void);
extern int keydown_event;


void set_key_state(int state);
void set_key(int channel, int state);
void set_key_state1(int state);

int read_key_state();

void set_uncertain_count(int count);
void process_key_chattering();

