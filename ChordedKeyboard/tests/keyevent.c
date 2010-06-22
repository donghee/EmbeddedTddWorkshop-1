#include "keyevent.h"

int key_state=0;
int _key_state=0;
int _uncertain_count;

int _state=0;

int _event=NOEVT;

int keydown_event=0;

void init_states() {
  key_state=0;
   _state=0;
}
void keydown_event_callback() {
  keydown_event=PRESSED;
}

void keydown_event_release_callback() {
  keydown_event=RELEASED;
}

//keydown_event_cb=(void *(void))keydown_event_callback;
void (*keydown_event_cb)(void) = keydown_event_callback;

void set_key_state(int state) {
  _key_state = state;
}

int read_key_state(){
	return key_state;
}

void set_uncertain_count(int count) {
	_uncertain_count = count;
	init_states();
}

int next_state(int inp, int k, int n) {
  if (!inp && k)
	return (k+1) % (n+1);
  else
	return inp;
}

void process_key_chattering() {
  _state = next_state(_key_state, _state, _uncertain_count);
  key_state =  0 < _state;
}

void key_step(int k) {
  set_key_state(k); 
  process_key_chattering(); 
}

int get_event() {
  if (key_state) {
	_event = PRESSED;
  } else {
	if (_event == PRESSED) {
	  _event = RELEASED;
	  return _event;
	}
	_event = NOEVT;
  }
  return _event;
}
