#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

//MockSupport mock;

//extern "C" {
//	#include "CppUTestExt/MockSupport_c.h"
//}
//
TEST_GROUP(PressButton)
{
    void setup() {
    }
    void teardown() {
        mock().clear();
    }
};

void _button_pressed()
{
    mock().actualCall("led_on");
}


TEST(PressButton, test_press_and_led_on)
{
    mock().expectOneCall("led_on");
 	//when button is pressed
    _button_pressed();
    // 	expect_call_led_on();
    mock().checkExpectations();
}

// TEST(PressButton, test_press_and_led_on) {
// 	//when started
// 	_exit_mainloop=1;
// 	start();
// 	//loop_step must be called continuously
// 	expect_call_loop_step();
// }

// TEST(PressButton, test_press_and_led_on) {
// 	//when loop_step is called
// 	loop_step();
// 	//is_pressed should have been called
// 	expect_call_is_pressed();
// 	set_return_value_for_is_pressed(1);
// 	expect_call_led_on();

// 	loop_step();
// 	expect_call_is_pressed();
// 	set_return_value_for_is_pressed(0);
// 	expect_call_led_off();
// 	//if is_pressed is true
// 	   //expect led_on is called
// 	//if is_pressed is false
// 	   //expect led_off is called
// }
