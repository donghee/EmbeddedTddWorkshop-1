/*
TODO: 
 X mock plugin 쓰도록 refactoring
 X 디렉토리 정리
 X _button_pressed에서 앞에 _ 빼기
 X led_on/off 구현
  X link-time substitute 이용.
  X TODO: 버튼 눌렀을때 led_off가 되네 수정필요.
 X is_pressed 단일 테스트
 X 전체 시스템 테스트 (누르면 Led 켜지고, 안누르면 꺼지는지)
 * bouncing 처리 test 만들기
*/


#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "press_button.h"
}

TEST_GROUP(Debouncing)
{
    void setup() {
    }

    void teardown() {
        
    }
};

TEST(Debouncing, test_button_on)
{
    int button_state;
    // set debounce time 20 ms
    set_debounce_time(20);
    // invoke button on event signal
    mock().expectOneCall("is_pressed").andReturnValue(1);
    // after debounce time 30ms
    mock().expectOneCall("delay").withParameter(30);
    // button is on
    button_state = process_debouning();
    LONGS_EQUAL(button_state , 1);
    // check expect
}

TEST(Debouncing, test_button_on1)
{
    // set debounce time
    // invoke button on event signal
    // before debounce time
    // button is off
    // check expect
}

TEST(Debouncing, test_button_off)
{
    // set debounce time
    // invoke button off event signal
    // before debounce time
    // button is on
    // check expect
}


TEST(Debouncing, test_button_off1)
{
    // set debounce time
    // invoke button off event signal
    // after debounce time
    // button is on
    // check expect
}
