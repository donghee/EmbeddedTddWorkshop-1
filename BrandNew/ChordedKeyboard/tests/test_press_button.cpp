#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
#include "press_button.h"
}

TEST_GROUP(PressButton)
{


    static void mock_led_on() {
        mock().actualCall("led_on");
    }

    static int mock_loop_step() {
        int shd_stop;
        shd_stop=mock().actualCall("loop_step").returnValue().getIntValue();
        return shd_stop;
    }

    void setup() {
        UT_PTR_SET(led_on,&mock_led_on);        
        UT_PTR_SET(loop_step,&mock_loop_step);        

    }

    void teardown() {
        mock().clear();
    }


    /*
    void loop_step() {
        mock().actualCall("loop_step");
        if (is_pressed() == 1) {
            led_on();
        }else {
            mock().actualCall("led_off");            
        }
    }

    int is_pressed() {
        int value = mock().actualCall("is_pressed").returnValue().getIntValue();
        return value;
        }*/

};



TEST(PressButton, test_press_and_led_on)
{
    mock().expectOneCall("led_on");
 	//when button is pressed
    _button_pressed();
    // 	expect_call_led_on();
    mock().checkExpectations();
}

TEST(PressButton, test_start) {
    mock().expectOneCall("loop_step").andReturnValue(1);
	//when started
	start();
	//loop_step must be called continuously
    mock().checkExpectations();

    //////////////////
    mock().expectOneCall("loop_step").andReturnValue(0);
    mock().expectOneCall("loop_step").andReturnValue(1); 
    start();
    mock().checkExpectations();

    // int _exit_mainloop=100;
    // mock().expectNCalls(_exit_mainloop, "loop_step").andReturnValue(1);
	// //when started
	// start();
	// //loop_step must be called continuously
    // mock().checkExpectations();

}

/*

TEST(PressButton, test_loop_step_process) {
    mock().expectOneCall("is_pressed").andReturnValue(1);
    mock().expectOneCall("led_on");
	//when loop_step is called
	loop_step();
    mock().checkExpectations();

	//if is_pressed is true
	   //expect led_on is called
	//if is_pressed is false
	   //expect led_off is called
}

TEST(PressButton, test_loop_step_process2) {
    mock().expectOneCall("is_pressed").andReturnValue(0);
    mock().expectOneCall("led_off");
    loop_step();
    mock().checkExpectations();
}
*/
