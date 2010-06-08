#include <iostream>
#include <string>
#include <sstream>

#include "CppUTest/CommandLineTestRunner.h"

extern "C"
{
#include <stdio.h>
#include "keyevent.h"
}

#define CHAR2VAL(x) ((x)=='-'?ON:OFF)
#define ASSERT_KEYSTATE(in,out)			\
	assert_keystate_location((in),(out), __FILE__,__LINE__)


/*
execute unit tests
cd ../ && ../watch.exe *.cpp - 'mingw32-make.exe'
cd ../ && make'
*/

void assert_keystate_location(char * in, char * out,const char* file, int line)
{
	int key_state = 0;
	int i=0;
	std::ostringstream ss;
	while ((*in))
		{
			set_key_state1(CHAR2VAL(*in));
			process_key_chattering();
			key_state = read_key_state();
			
			if (CHAR2VAL(*out)!=key_state)
				{
					ss<<(*out) << " expected but " << (*in) << " at " << i;
					FAIL_LOCATION(ss.str().c_str(),file,line);
				}
			in++;out++;i++;
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
	char in_s[]="__----";
	char ou_s[]="__----";

	set_uncertain_count(3);
	ASSERT_KEYSTATE(in_s,ou_s);
}

TEST(KeydownEvent, test_key_on_off1)
{
	char in_s[]="__--__";
	char ou_s[]="__----";

	set_uncertain_count(3);
	ASSERT_KEYSTATE(in_s,ou_s);
}

TEST(KeydownEvent, test_key_on_off2)
{
	char in_s[]="__--___";
	char ou_s[]="__----_";

	set_uncertain_count(3);
	ASSERT_KEYSTATE(in_s,ou_s);

	char in_s1[]="__--___";
	char ou_s1[]="__----_";

	set_uncertain_count(3);
	ASSERT_KEYSTATE(in_s1,ou_s1);

}
