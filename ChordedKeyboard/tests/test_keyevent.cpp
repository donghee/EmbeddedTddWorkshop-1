#include "CppUTest/CommandLineTestRunner.h"

extern "C"
{
#include <stdio.h>
#include "keyevent.h"
}

#define CHAR2VAL(x) ((x)=='-'?ON:OFF)

/*
execute unit tests
cd ../ && ../watch.exe *.cpp - 'mingw32-make.exe'
*/

void assert_keystate(char * in, char * out)
{
	int key_state = 0;
	while ((*in))
		{
			set_key_state1(CHAR2VAL(*in));
			process_key_chattering();
			key_state = read_key_state();
			
			LONGS_EQUAL(CHAR2VAL(*out), key_state);
			//printf("%c %c\n",*in,*out);
			in++;out++;
		}

}


TEST_GROUP(KeydownEvent)
{
	void setup()
	{
		keydown_event_count=0;

		for(int i=0; i <5; i++) {
			keydown_event_counts[i]=0;
		}
	}
	void teardown()
	{
	}
};

TEST(KeydownEvent, test_keydown_event_count)
{
	//key_state=off
	set_key(0, OFF);
	//no event
	LONGS_EQUAL(0, keydown_event_count);

	//key_state=on
	set_key_state(ON);

	//assert keydown event count = 1
	LONGS_EQUAL(1, keydown_event_count);
	LONGS_EQUAL(1, keydown_event_count);

	set_key_state(OFF);set_key_state(ON);
	//assert keydown event count = 2
	LONGS_EQUAL(2, keydown_event_count);
}

TEST(KeydownEvent, test_keydown_event)
{
	//key_state=off
	set_key_state(OFF);
	//key_state=on
	set_key_state(ON);
	//assert keydown event = pressed 
	LONGS_EQUAL(PRESSED, keydown_event);
	//key_state=off
	set_key_state(OFF);
	//assert keydown event = !pressed 
	LONGS_EQUAL(RELEASED, keydown_event);
}


TEST(KeydownEvent, test_key_on)
{
	// real value -> filtered value
	// 001111 -> 001111
	char in_s[]="__----";
	char ou_s[]="_-----";

	set_uncertain_count(3);
	assert_keystate(in_s,ou_s);
}

TEST(KeydownEvent, test_key_off)
{
	//	unsigned short test[] = {0,1,1,1,1};
	// 001100 -> 001111	
	int input[] = {OFF,OFF,ON,ON,OFF,OFF};
	int output[] = {OFF,OFF,ON,ON,ON,ON};

	int key_state;
	//	key_state = read_key_state();
	set_uncertain_count(3);

	set_key_state1(input[1]);
	process_key_chattering();
	key_state = read_key_state();
	LONGS_EQUAL(output[1], key_state);	

	set_key_state1(input[2]);
	process_key_chattering();
	key_state = read_key_state();
	LONGS_EQUAL(output[2], key_state);	

	set_key_state1(input[3]);
	process_key_chattering();
	key_state = read_key_state();
	LONGS_EQUAL(output[3], key_state);	

	// set_key_state1(input[4]);
	// process_key_chattering();
	// key_state = read_key_state();
	// LONGS_EQUAL(ON , key_state);	
	
}
