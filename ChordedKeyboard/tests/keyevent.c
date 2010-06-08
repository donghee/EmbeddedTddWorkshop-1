#include "keyevent.h"

int key_state=0;
int _key_state=0;
int _uncertain_count;
int _state=0;


void set_key_state(int state) {
	_key_state = state;
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
  _state = next_state(_key_state, _state, _uncertain_count);
  key_state =  0 < _state;
}
