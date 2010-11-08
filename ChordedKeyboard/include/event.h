#define PRESSED 1
#define RELEASE 2
#define NOEVT 0

extern int get_event();
extern int (*_process_debouncing)(int);

