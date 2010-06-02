#include "keyevent.h"

int keydown_event_count=0;
int keydown_event_counts[]={0,0,0,0,0};
int keydown_event=0;

int key_state=0;

int _p_key_state =0;
int _key_state=0;
int _key_states[]={0,0,0,0,0};

int _channel=0;
int _uncertain_count=0;
int uncertain_flag= 0;

void keydown_event_callback() {
	keydown_event_counts[_channel]++;
	keydown_event_count = keydown_event_counts[_channel];
	keydown_event=PRESSED;
}

void keydown_event_release_callback() {
	keydown_event=RELEASED;
}

//keydown_event_cb=(void *(void))keydown_event_callback;
void (*keydown_event_cb)(void) = keydown_event_callback;

void set_key(int channel, int state) {
	_channel=channel;
	set_key_state(state);
}

void set_key_state(int state) {
	_key_state=_key_states[_channel];

	if (_key_state==0 && state==1) {
		keydown_event_cb();
	}

	if (_key_state==1 && state==0) {
		keydown_event_release_callback();
	}

	_key_states[_channel]=state;
}

void set_key_state1(int state) {

	_key_state = state;
}

int read_key_state(){
	return key_state;
}

void reset_key_state() {
	_p_key_state = OFF;
	uncertain_flag = 0;
}


void set_uncertain_count(int count) {
	_uncertain_count = count;
	reset_key_state();
}


void process_key_chattering() {
	if (_key_state||_p_key_state) {
		if((!_key_state) && _p_key_state){
			_uncertain_count--;
		}
    	_p_key_state = _key_state;
		key_state = ON;

		return;
	}


	key_state=(_uncertain_count<3);

	if (key_state) {
		if (_uncertain_count  == 1) {
			key_state = OFF;
			_uncertain_count =3;
		}
		_uncertain_count--;

	}
	_p_key_state = _key_state;
}
