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
			set_key_state(CHAR2VAL(*in));
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
	}
	void teardown()
	{
	}
};

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

TEST(KeydownEvent, test_key_press_release)
{
	//char in_s[]="_--___";
	// int event;
	// int key;
	set_uncertain_count(3);

	key_step(CHAR2VAL('_'));
	LONGS_EQUAL(NOEVT, get_event());

	key_step(CHAR2VAL('-'));
	LONGS_EQUAL(PRESSED, get_event());

	key_step(CHAR2VAL('-'));
	LONGS_EQUAL(PRESSED, get_event());

	key_step(CHAR2VAL('_'));
	LONGS_EQUAL(PRESSED, get_event());

	key_step(CHAR2VAL('_'));
	LONGS_EQUAL(PRESSED, get_event());

	key_step(CHAR2VAL('_'));
	LONGS_EQUAL(RELEASED, get_event());

	key_step(CHAR2VAL('_'));
	LONGS_EQUAL(NOEVT, get_event());

	key_step(CHAR2VAL('-'));
	LONGS_EQUAL(PRESSED, get_event());

}
