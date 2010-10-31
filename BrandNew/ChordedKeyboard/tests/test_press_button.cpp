#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
#include "press_button.h"
}

TEST_GROUP(PressButton)
{
    static int mock_loop_step() {
        int shd_stop;
        shd_stop=mock().actualCall("loop_step").returnValue().getIntValue();
        return shd_stop;
    }
    void setup() {
        UT_PTR_SET(loop_step,&mock_loop_step);        

    }
    void teardown() {
    }
};

TEST(PressButton, test_start) {
    mock().expectOneCall("loop_step").andReturnValue(1);
	start();
}

TEST(PressButton, test_multiful_loop_step) {    
    mock().expectOneCall("loop_step").andReturnValue(0);
    mock().expectOneCall("loop_step").andReturnValue(1); 
    start();

    int _nloop=5;
    int shd_stop=1;
    mock().expectNCalls(_nloop-1, "loop_step").andReturnValue(!shd_stop);
    mock().expectOneCall("loop_step").andReturnValue(shd_stop);
	start();
}


TEST_GROUP(LoopStepProcess)
{
    static int mock_is_pressed() {
        int pressed;
        pressed = mock().actualCall("is_pressed").returnValue().getIntValue();
        return pressed;
    }

    static void mock_led_on() {
        mock().actualCall("led_on");
    }

    static void mock_led_off() {
        mock().actualCall("led_off");
    }

    void setup() {
        UT_PTR_SET(is_pressed,&mock_is_pressed);        
        UT_PTR_SET(led_on,&mock_led_on);
        UT_PTR_SET(led_off,&mock_led_off);
    }

    void teardown() {
        mock().clear();
    }
};

TEST(LoopStepProcess, test_press_and_led_on)
{
    mock().expectOneCall("led_on");
 	//when button is pressed
    _button_pressed();
}

TEST(LoopStepProcess, test_loop_step_process) {
    mock().expectOneCall("is_pressed").andReturnValue(1);
    mock().expectOneCall("led_on"); 
	loop_step();
}

TEST(LoopStepProcess, test_loop_step_process2) {
    mock().expectOneCall("is_pressed").andReturnValue(0);
    mock().expectOneCall("led_off");
    loop_step();
}
