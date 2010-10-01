#include <iostream>
#include <string>
#include <sstream>

#include "CppUTest/CommandLineTestRunner.h"

extern "C"
{
#include <stdio.h>
#include <string.h>
#include "keyevent.h"
#include "time.h"
}


#define CHAR2VAL(x) ((x)=='-'?ON:OFF)
#define CHAR2EVT(x) ((x)=='^'?PRESSED:((x)=='v'?RELEASED:NOEVT) )

#define ASSERT_KEYSTATE(in,out)			\
	assert_keystate_location((in),(out), __FILE__,__LINE__)

#define ASSERT_KEYSTATE_t(in,out)			\
    assert_keystate_t_location((in),(out), __FILE__,__LINE__)

unsigned long __ctime = 0;


void assert_debouncing_buffer(char in,char out,
               int exp_ctime,
               int exp_last_debounce_time)
{
    int actual;
    unsigned long _ctime;
    my_delay(5);
    _ctime = my_millis();
    LONGS_EQUAL(exp_ctime, _ctime);
    set_key(CHAR2VAL(in));
    process_debouncing();
    actual = read_key();
    LONGS_EQUAL(CHAR2VAL(out),actual);
    LONGS_EQUAL(exp_last_debounce_time,last_debounce_time);
}

void assert_keystate_t_location(char * in, char * out,const char* file, int line) {
  // int key_state = 0;
  // int i=0;
  // std::ostringstream ss;  

}

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
    
    static void my_mock_delay(unsigned long millis) {
        __ctime = __ctime + millis;
    }

    static unsigned long my_mock_millis(void) {
        return __ctime;
    }


	void setup()
	{
        my_delay=my_mock_delay;
        my_millis=my_mock_millis;
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
};

TEST(KeydownEvent, test_key_press_release)
{
    // char in_s[]="_--_____-__-___";
	// char ev_s[]=" ^   v  ^     v"; // ^: PRESSED,  v: RELEASED, ' ': NOEVT
	// int i=0;
	// set_uncertain_count(3);

	// while (*(in_s+i)) {
	//   key_step(CHAR2VAL(*(in_s+i)));
	//   LONGS_EQUAL(CHAR2EVT(*(ev_s+i)), get_event());
	//   i++;
	// }
}

// TEST_GROUP(TimeBasedDebouncing)
// {
// 	void setup()
// 	{
// 	}
// 	void teardown()
// 	{
// 	}
// };

// TEST(TimeBasedDebouncing, test1)
// {
//     // char in_s[]="_-_--------"; //each one is 5 ms
// 	// char ou_s[]="__________-";

// 	// set_debounce_period(30); //milli sec
// 	//	ASSERT_KEYSTATE_t(in_s,ou_s);
// }


TEST(KeydownEvent, test2){
    char inputBuffer[]    = "_-----";
    char expectedBuffer[] = "_____-";

    int s_rate = 5, exp_time=5, exp_last_deb_time=0;
    int i=0;

    set_sampling_rate(s_rate);
    set_debounce_period(15);
    
    assert_debouncing_buffer(inputBuffer[i],expectedBuffer[i],
                             exp_time,
                             exp_last_deb_time);

    exp_last_deb_time=10;i++;

    for(; i < strlen(inputBuffer); i++) {
        exp_time+=s_rate;
        assert_debouncing_buffer(inputBuffer[i],expectedBuffer[i],
                                 exp_time,
                                 exp_last_deb_time);
    }
}

