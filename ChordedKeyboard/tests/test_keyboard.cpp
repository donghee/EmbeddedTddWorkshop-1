#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "press_button.h"
#include "debounce.h"
#include "event.h"
}

TEST_GROUP(Keyboard)
{
    static int mock_is_pressed(int button) {
        int pressed;
        pressed = mock().actualCall("is_pressed").withParameter("button", (int) button).returnValue().getIntValue();
        return pressed;
    }

    static void mock_delay(long unsigned millisecs) {
        mock().actualCall("delay").withParameter("millisecs",(int) millisecs);
    }

    static unsigned long mock_cmillis() {
        return (unsigned long) mock().actualCall("cmillis").returnValue().getIntValue();
    }

    static int mock_loop_step() {
        int shd_stop;
        shd_stop=mock().actualCall("loop_step").returnValue().getIntValue();
        return shd_stop;
    }
    

    int db_time;
    int button_state;
    void setup() {
        db_time = 20;
        UT_PTR_SET(is_pressed,&mock_is_pressed);
        // UT_PTR_SET(button_is_pressed,&mock_button_is_pressed);        
        UT_PTR_SET(_delay,&mock_delay);
        UT_PTR_SET(cmillis,&mock_cmillis);
        UT_PTR_SET(loop_step,&mock_loop_step);                
    }

    void teardown() {
        
    }

};

void mock_expect_buttons_scenario(int* buttons) 
{
    int i;
    
    for (i=0; i<5; i++) {
        mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(buttons[i]);
    }
    
}


TEST(Keyboard, test_read_all_buttons)
{
    int button_code = 0;
    int buttons_scenario[5] = [BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF];
            
    set_composite_wakeup(100);
    mock_expect_buttons_scenario(buttons_scenario)    
    button_code = read_all_buttons();
    LONGS_EQUAL(1, button_code);
}

TEST(Keyboard, test_read_all_buttons2)
{
    int button_code = 0; 
    set_composite_wakeup(100);
    int buttons_scenario[5] = [BUTTON_ON, BUTTON_OFF, BUTTON_ON, BUTTON_OFF, BUTTON_OFF];
    
    mock_expect_buttons_scenario(buttons_scenario);
    
    button_code = read_all_buttons();
    LONGS_EQUAL(5, button_code);
}

TEST(Keyboard, test_read_all_buttons_on)
{
    int button_code = 0; 
    set_composite_wakeup(100);
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_ON);
    mock().expectOneCall("is_pressed").withParameter("button",1).andReturnValue(BUTTON_ON);
    mock().expectOneCall("is_pressed").withParameter("button",2).andReturnValue(BUTTON_ON);
    mock().expectOneCall("is_pressed").withParameter("button",3).andReturnValue(BUTTON_ON);
    mock().expectOneCall("is_pressed").withParameter("button",4).andReturnValue(BUTTON_ON);
    button_code = read_all_buttons();
    LONGS_EQUAL(31, button_code);
}

            



TEST(Keyboard, test_is_pressed_0)
{
    //    int button_code = 0; 
    
    set_composite_wakeup(100);
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_ON);
    mock().expectOneCall("delay").withParameter("millisecs", 100);
    button_code = mock().expectOneCall("read_all_buttons").andReturnValue(1);
    //mock().expectOneCall("send_serial").withParameter("btn_code", button_code);
    start2();
// is any_presse buton?
//  delay 100 secs
//  read all button
//  make buttons composition
//  send serial

}
