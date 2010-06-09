#include "keyevent.h"

int key_state=0;
int _key_state=0;
int _uncertain_count;

int _state=0;
int _pstate=0;

int keydown_event=0;

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
  /* if (_key_state==0 && state==1) { */
  /* 	keydown_event_cb(); */
  /* } */
  /* if (_key_state==1 && state==0) { */
  /* 	keydown_event_release_callback(); */
  /* } */

}

int read_key_state(){
	return key_state;
}

void set_uncertain_count(int count) {
	_uncertain_count = count;
}

int next_state(inp, k, n) {
  if (!inp && k)
	return (k+1) % (n+1);
  else
	return inp;
}

void process_key_chattering() {
  _pstate = _state;
  _state = next_state(_key_state, _state, _uncertain_count);
  key_state =  0 < _state;
}

int read_keydown_event() {
  if (_state == 1 &&  _pstate == 0) {
	keydown_event=PRESSED;
  } else if (_state == 0 && _pstate == 3) {
	keydown_event=RELEASED;
 	/* keydown_event_release_callback();  */
  } else if (_pstate == 0) {
	keydown_event = NOP;
  }
  return keydown_event;
}
