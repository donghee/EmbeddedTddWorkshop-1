#include "keyevent.h"
#include "time.h"

int key_state=0;
int _key_state=0;
int p_key_state=0;

int _uncertain_count;

int _state=0;

int _event=NOEVT;

int keydown_event=0;

int sample_rate;

int debounce_period;
unsigned long last_debounce_time=0;

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
  p_key_state=key_state;
  key_state =  0 < _state;
}

void key_step(int k) {
  set_key_state(k); 
  //  process_key_chattering(); 
  process_debouncing();

}

int get_event() {

  if  (!p_key_state && key_state)
	_event=PRESSED;
  else if (p_key_state && !key_state)
	_event=RELEASED;
  else
	_event=NOEVT;
  return _event;
}

void set_debounce_period(int delay) {
    debounce_period = delay;
}


void set_sampling_rate(int millis) {
    sample_rate = millis;
}

void reset_last_debounce_time() {
    last_debounce_time = my_millis();
}

void process_debouncing() {
	if (_key_state != p_key_state) {
        reset_last_debounce_time();
    }

    if ((my_millis() - last_debounce_time) > debounce_period) {
        key_state = _key_state;
        //        reset_last_debounce_time();
    }
            
    p_key_state = _key_state;
}


int read_key() {
    return key_state;
}

void set_key(int state) {
    _key_state = state;
}

