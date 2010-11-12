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
 X get_event 테스트 케이스 만들기
  * NOEVT 테스트 케이스
 * 두개 버튼 테스트 만들기
 X 준비물 챙기기 (폼보드, 알루미늄테이프, 니퍼, 가위, 전선)
 X mock expect button sequence ? scenario
 * 개발환경 공유
 * makefile 합치기
 * loop_step 사용하기
 * button_pressed 시리얼로 연결하기
 
*/


#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "press_button.h"
#include "debounce.h"
#include "event.h"
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

    static void mock_expect_button_sequence(int button1, int db_time, int button2 )
    {
        mock().expectOneCall("is_pressed").andReturnValue(button1);
        mock().expectOneCall("delay").withParameter("millisecs",db_time);
        mock().expectOneCall("is_pressed").andReturnValue(button2);
    }
    
};

TEST(Debouncing, test_button_on)
{
    button_state = BUTTON_OFF;
    set_debounce_time(db_time);

    mock_expect_button_sequence(BUTTON_ON,db_time, BUTTON_ON);

    button_state=process_debouncing(button_state);
    LONGS_EQUAL(BUTTON_ON,button_state);
}

TEST(Debouncing, test_button_on1)
{
    button_state = BUTTON_OFF;
    set_debounce_time(db_time);

    mock_expect_button_sequence(BUTTON_ON,db_time, BUTTON_OFF);

    button_state=process_debouncing(button_state);
    LONGS_EQUAL(BUTTON_OFF, button_state);
}

TEST(Debouncing, test_button_event)
{
    set_debounce_time(db_time);
    int button_event = NOEVT; 
    mock_expect_button_sequence(BUTTON_ON, db_time, BUTTON_ON);
    button_event = get_event();
    LONGS_EQUAL(PRESSED, button_event);

    // p_button_state = ON
    mock_expect_button_sequence(BUTTON_OFF, db_time, BUTTON_OFF);
    button_event = get_event();
    LONGS_EQUAL(RELEASE, button_event);

    // p_button_state = OFF
    // mock_expect_button_sequence(BUTTON_OFF, db_time, BUTTON_OFF);
    // button_event = get_event();
    // LONGS_EQUAL(NOEVT, button_event);

    // TODO: make NOEVT test case
    mock_expect_button_sequence(BUTTON_ON, db_time, BUTTON_OFF);
    button_event = get_event();
    LONGS_EQUAL(NOEVT, button_event);
}
