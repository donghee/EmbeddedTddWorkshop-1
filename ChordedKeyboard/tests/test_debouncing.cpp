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
  X 개발환경 공유
  X makefile 합치기
  * loop_step 사용하기
  * button_pressed 시리얼로 연결하기 
  *  millis() overflow 처리.limit.h  (max - t1) + t2 or t2- t1
  * BUTTON_ON/OFF/DEBOUNCING_ON/OFF enum으로 바꾸기 
  * extern 빼기. 펑션포인터 선언 빼기 -> *.c 내용 헤더로 모아넣기
  * 간단한 버전 debouncing 코드 만들기 
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

    int db_time;
    int button_state;
    void setup() {
        db_time = 20;
        UT_PTR_SET(is_pressed,&mock_is_pressed);
        // UT_PTR_SET(button_is_pressed,&mock_button_is_pressed);        
        UT_PTR_SET(_delay,&mock_delay);
        UT_PTR_SET(cmillis,&mock_cmillis);
    }

    void teardown() {
        
    }

};

void mock_expect_button_sequence(int button1, int db_time, int button2 )
{
    mock().expectOneCall("cmillis").andReturnValue(0);
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(button1);
    mock().expectOneCall("cmillis").andReturnValue(db_time);
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(button2);
}


int process_and_check(int expected, int current) {
    int button_state;
    button_state=process_debouncing(current);
    LONGS_EQUAL(expected,button_state);
    return button_state;
}

void check_states_scenario_btn0(int current, int occurd_event, int expect) 
{
    int button_state;
    set_current_state2(0,current);
    occur2(0,occurd_event);
    button_state = get_current_state2(0);
    LONGS_EQUAL(expect, button_state);
}


TEST(Debouncing, test_temp)
{
    check_states_scenario_btn0(ST_BUTTON_RELEASED, EV_BUTTON_ON, ST_DEB_FOR_PR);
}

TEST(Debouncing, test_temp1)
{
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_ON);
    check_states_scenario_btn0(ST_DEB_FOR_PR, EV_WAKE_UP, ST_BUTTON_PRESSED);
}


TEST(Debouncing, test_temp2)
{
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_OFF);
    check_states_scenario_btn0(ST_DEB_FOR_PR, EV_WAKE_UP, ST_BUTTON_RELEASED);    
}

TEST(Debouncing, test_temp3)
{
    check_states_scenario_btn0(ST_BUTTON_PRESSED, EV_BUTTON_OFF, ST_DEB_FOR_RE);
}


TEST(Debouncing, test_temp4)
{
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_OFF);
    check_states_scenario_btn0(ST_DEB_FOR_RE, EV_WAKE_UP, ST_BUTTON_RELEASED);
}


TEST(Debouncing, test_temp5)
{
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_ON);
    check_states_scenario_btn0(ST_DEB_FOR_RE, EV_WAKE_UP, ST_BUTTON_PRESSED);
}

TEST(Debouncing, test_two_buttons1) 
{
    set_current_state2(0, ST_BUTTON_RELEASED);
    occur2(0,EV_BUTTON_ON);
    button_state = get_current_state2(0);
    LONGS_EQUAL(ST_DEB_FOR_PR, button_state);
}

TEST(Debouncing, test_two_buttons2)
{
    set_current_state2(0, ST_BUTTON_RELEASED);
    set_current_state2(1, ST_BUTTON_RELEASED);
    occur2(0,EV_BUTTON_ON);

    button_state = get_current_state2(0);
    LONGS_EQUAL(ST_DEB_FOR_PR, button_state);
    
    button_state = get_current_state2(1);
    LONGS_EQUAL(ST_BUTTON_RELEASED, button_state);
}


TEST(Debouncing, test_two_buttons3)
{

    set_current_state2(0, ST_DEB_FOR_PR);
    set_current_state2(1, ST_DEB_FOR_PR);

    mock().expectOneCall("is_pressed").withParameter("button", 0).andReturnValue(BUTTON_ON);        
    occur2(0,EV_WAKE_UP);

    button_state = get_current_state2(0);
    LONGS_EQUAL(ST_BUTTON_PRESSED, button_state);
    
    button_state = get_current_state2(1);
    LONGS_EQUAL(ST_DEB_FOR_PR, button_state);
}

TEST(Debouncing, test_two_buttons4)
{

    set_current_state2(0, ST_DEB_FOR_PR);
    set_current_state2(1, ST_DEB_FOR_PR);

    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_OFF);
    occur2(0,EV_WAKE_UP);

    button_state = get_current_state2(0);
    LONGS_EQUAL(ST_BUTTON_RELEASED, button_state);
    
    button_state = get_current_state2(1);
    LONGS_EQUAL(ST_DEB_FOR_PR, button_state);
}

TEST(Debouncing, test_two_buttons5)
{
    set_current_state2(0, ST_DEB_FOR_PR);
    mock().expectOneCall("is_pressed").withParameter("button",0).andReturnValue(BUTTON_OFF);
    occur2(0,EV_WAKE_UP);
    // set current button0 state is st_deb
    // occur event wake up
    // mock expect call is_pressed(0)  button off
    // button pressed event occur when times up
     // mock expect call ('composite buttons')    
     // mock expect call ('send button event')

    // current button0 state is ST_BUTTON_PRESSED
}
 




/*
TEST(XXXX, test_temp)
{
    set_current_state2(0, ST_BUTTON_RELEASED);
    occur2(0,EV_BUTTON_ON);
    check_cs2(0, ST_DEB_FOR_PR);
    /////////////////////////////
    set_current_state2(0, ST_BUTTON_PRESSED);
    set_current_state2(1, ST_BUTTON_RELEASED);
    occur2(1,EV_BUTTON_ON);
    check_cs2(0, ST_DEB_FOR_PR);
    check_cs2(1, ST_BUTTON_RELEASED);
    

}
*/

TEST(Debouncing, test_button_on)
{
    button_state = BUTTON_OFF;
    set_debounce_time(db_time);

    mock_expect_button_sequence(BUTTON_ON,db_time, BUTTON_ON);

    button_state=process_and_check(DEBOUNCING_ON, button_state);
    button_state=process_and_check(BUTTON_ON, button_state);
}


TEST(Debouncing, test_button_on1)
{
    button_state = BUTTON_OFF;
    set_debounce_time(db_time);

    mock_expect_button_sequence(BUTTON_ON,db_time, BUTTON_OFF);

    button_state=process_and_check(DEBOUNCING_ON, button_state);
    button_state=process_and_check(BUTTON_OFF, button_state);
}

TEST(Debouncing, test_button_pressed_event)
{
    int button_event;    
    set_debounce_time(db_time);

    mock_expect_button_sequence(BUTTON_ON, db_time, BUTTON_ON);
    button_event = get_event();
    LONGS_EQUAL(PRESSED, button_event);

}

TEST(Debouncing, test_button_released_event)
{
    int button_event;

    p_button_state = BUTTON_ON;

    set_debounce_time(db_time);
    mock_expect_button_sequence(BUTTON_OFF, db_time, BUTTON_OFF);
    button_event = get_event();
    LONGS_EQUAL(RELEASE, button_event);
}

TEST(Debouncing, test_button_less_db_time)
{
    int button_event;
    p_button_state = BUTTON_ON;
    //TODO less db_time
    set_debounce_time(db_time);
    mock_expect_button_sequence(BUTTON_OFF, db_time, BUTTON_OFF);
    button_event = get_event();
    LONGS_EQUAL(RELEASE, button_event);
    // LONGS_EQUAL(1, button_event);    
}

/* 
// p_button_state = OFF
// mock_expect_button_sequence(BUTTON_OFF, db_time, BUTTON_OFF);
// button_event = get_event();
// LONGS_EQUAL(NOEVT, button_event);

// TODO: make NOEVT test case
mock_expect_button_sequence(BUTTON_ON, db_time, BUTTON_OFF);
button_event = get_event();
LONGS_EQUAL(NOEVT, button_event);
}

*/


