#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "fake_digital_controller.h"
#include "keyboard.h"    
}

static int btn_pins[5] = {1,2,3,4,5};

TEST_GROUP(Keyboard2)
{
    void setup() {
       digitalPinSetting();
       set_buttons_pin(btn_pins);    
    }

    void teardown() {
    }
};


static void fake_buttons_on(int btn1, int btn2, int btn3, int btn4, int btn5)
{
    fake_digitalWrite(1,!btn1);
    fake_digitalWrite(2,!btn2);
    fake_digitalWrite(3,!btn3);
    fake_digitalWrite(4,!btn4);
    fake_digitalWrite(5,!btn5);
}

TEST(Keyboard2, test_is_pressed_1) {
    fake_digitalWrite(1, HIGH);
    LONGS_EQUAL(false, is_pressed(1));
}

TEST(Keyboard2, test_is_pressed_1_2) {
    fake_digitalWrite(1, LOW);        
    fake_digitalWrite(2, HIGH);    
    LONGS_EQUAL(true, is_pressed(1));
    LONGS_EQUAL(false, is_pressed(2));
}

TEST(Keyboard2, test_is_pressed_default_low) {
    LONGS_EQUAL(true, is_pressed(1));
    LONGS_EQUAL(true, is_pressed(2));
}

TEST(Keyboard2, test_set_buttons_mode) 
{
   int pins[5] = {3,5,6,7,8};
   set_buttons_pin(pins);
   fake_digitalWrite(5, HIGH);    
   LONGS_EQUAL(false, is_pressed(2))
}


TEST(Keyboard2, test_read_all_buttons) 
{
    fake_buttons_on(BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    LONGS_EQUAL(1, read_all_buttons());
}


TEST(Keyboard2, test_read_all_buttons_2)
{
    fake_buttons_on(BUTTON_ON,BUTTON_ON,BUTTON_ON,BUTTON_ON,BUTTON_ON);
    LONGS_EQUAL(31, read_all_buttons());
}

TEST(Keyboard2, test_read_all_buttons_3)
{
    fake_buttons_on(BUTTON_ON,BUTTON_OFF,BUTTON_ON,BUTTON_OFF,BUTTON_ON);
    LONGS_EQUAL(21, read_all_buttons());
}

TEST(Keyboard2, test_one_loop)
{
    unsigned long ctime = 0;
    set_composite_wakeup(20);
    fake_buttons_on(BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    fake_set_ctime(ctime);
    wait_for_debouncing();
    ctime = get_ctime();
    LONGS_EQUAL(20, ctime);
    LONGS_EQUAL(1, read_all_buttons());
}
// TODO: 키 조합 테스트 케이스 만들기
// 하나 눌렀을때
// 몇초후 2개 누르기
// 최종

TEST(Keyboard2, test_any_button_pressed)
{
    fake_buttons_on(BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    LONGS_EQUAL(false, any_button_pressed());

    fake_buttons_on(BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    LONGS_EQUAL(true, any_button_pressed());
}

TEST(Keyboard2, test_loop_keyboard_step)
{
    int shd_stop;
    fake_buttons_on(BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    fake_buttons_on(BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    shd_stop = loop_keyboard_step();
    LONGS_EQUAL(0, shd_stop);
}

TEST(Keyboard2, test_one_wait_for_composition)
{
    unsigned long ctime = 0;
    set_composite_wakeup(20);

    fake_buttons_on(BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    fake_set_ctime(ctime);
    wait_for_debouncing();    
    LONGS_EQUAL(1, read_all_buttons());

    fake_buttons_on(BUTTON_ON, BUTTON_ON, BUTTON_OFF, BUTTON_OFF, BUTTON_OFF);
    wait_for_composite();
    ctime = get_ctime();
    LONGS_EQUAL(40, ctime);

    fake_buttons_on(BUTTON_ON, BUTTON_ON, BUTTON_ON, BUTTON_OFF, BUTTON_OFF);
    wait_for_composite();
    ctime = get_ctime();
    LONGS_EQUAL(60, ctime);

}

// loop_step을 mock 사용하지 않고 하는 방법 있을까?
// TEST(Keyboard2, test_loop_step)
// {
//     int keycode;
//     set_composite_wakeup(20);

//  // is any_presse buton?
//  // delay 100 secs
//  // read all buttons
//  // send serial
//     mock().expectOneCall("any_button_pressed").andReturnValue(true);
//     mock().expectOneCall("wait_for_composite");
//     mock().expectOneCall("read_all_buttons").andReturnValue(keycode);
//     mock().expectOneCall("send_serial").withParameter("code", keycode).andReturnValue(1);
//     mock().expectOneCall("any_button_pressed").andReturnValue(false);
//     LONGS_EQUAL(1, loop_keyboard_step());
// }

