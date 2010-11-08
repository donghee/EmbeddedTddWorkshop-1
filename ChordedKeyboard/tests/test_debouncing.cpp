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
 X bouncing 처리 test 만들기/구현
 X led_on/ led_off 따로 분리하기
  X link-time substitute 제거하기 (레이어 추가) (util/imp.c)
 X 실제 통합테스트
  X testpoint로 bouncing처리 확인하기
 * get_event 테스트 케이스 만들기 
 * 두개 버튼 테스트 만들기
*/


#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "press_button.h"
#include "debounce.h"                   
}

TEST_GROUP(Debouncing)
{
    int current_time;
    static int mock_is_pressed() {
        int pressed;
        pressed = mock().actualCall("is_pressed").returnValue().getIntValue();
        return pressed;
    }
    
    static void mock_delay(long unsigned millisecs) {
        mock().actualCall("delay").withParameter("millisecs",(int) millisecs);
    }    
    int db_time;
    int button_state;
    void setup() {
        db_time = 20;
        UT_PTR_SET(is_pressed,&mock_is_pressed);
        UT_PTR_SET(_delay,&mock_delay);        
    }

    void teardown() {
        
    }
};

TEST(Debouncing, test_button_on)
{

    button_state = BUTTON_OFF;
    set_debounce_time(db_time);
    mock().expectOneCall("is_pressed").andReturnValue(BUTTON_ON);
    mock().expectOneCall("delay").withParameter("millisecs",db_time);
    mock().expectOneCall("is_pressed").andReturnValue(BUTTON_ON);
    button_state=process_debouncing(button_state);
    LONGS_EQUAL(button_state , BUTTON_ON);
}

TEST(Debouncing, test_button_on1)
{
    button_state = BUTTON_OFF;
    set_debounce_time(db_time);
    mock().expectOneCall("is_pressed").andReturnValue(BUTTON_ON);
    mock().expectOneCall("delay").withParameter("millisecs",db_time);
    mock().expectOneCall("is_pressed").andReturnValue(BUTTON_OFF);
    button_state=process_debouncing(button_state);
    LONGS_EQUAL(button_state, BUTTON_OFF);
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
