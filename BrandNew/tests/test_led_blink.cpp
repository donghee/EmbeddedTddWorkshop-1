#include "CppUTest/CommandLineTestRunner.h"

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

TEST_GROUP(LedBlink) {
	int ledPin;
	setup() {
		ledPin = 13;
	}
	teardown(){
	}
};

TEST(LedBlink, test_press_and_led_on) {
	//when button is pressed
	_button_pressed();
	//check light is on
	expect_call_led_on();
}

TEST(LedBlink, test_press_and_led_on) {
	//when started
	_exit_mainloop=1;
	start();
	//loop_step must be called continuously
	expect_call_loop_step();
}

TEST(LedBlink, test_press_and_led_on) {
	//when loop_step is called
	loop_step();
	//is_pressed should have been called
	expect_call_is_pressed();
	set_return_value_for_is_pressed(1);
	expect_call_led_on();

	loop_step();
	expect_call_is_pressed();
	set_return_value_for_is_pressed(0);
	expect_call_led_off();
	//if is_pressed is true
	   //expect led_on is called
	//if is_pressed is false
	   //expect led_off is called
}
