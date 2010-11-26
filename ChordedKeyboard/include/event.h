#define PRESSED 1
#define RELEASE 2
#define NOEVT 0

#define ST_BUTTON_RELEASED 0 
#define ST_DEB_FOR_PR 1
#define ST_BUTTON_PRESSED 2
#define ST_DEB_FOR_RE 3

#define EV_BUTTON_OFF 0
#define EV_BUTTON_ON 1
#define EV_WAKE_UP 2



extern int get_event();

extern int p_button_state;


extern void set_current_state(int state);
extern void occur(int event);
extern int get_current_state();


extern void set_current_state2(int button, int state);
extern void occur2(int button, int event);
extern int get_current_state2(int button);
