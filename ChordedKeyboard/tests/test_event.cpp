/*
  TODO
 * get_event 테스트 케이스 만들기 
 * 두개 버튼 테스트 만들기
*/

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
#include "debounce.h"
#include "event.h"
}

TEST_GROUP(ButtonEvent)
{
    static int mock_process_debouncing(int button_state) {
        mock().actualCall("process_debouncing").withParameter("button_state",button_state).returnValue().getIntValue();
        return 1;
    }

    void setup() {
        UT_PTR_SET(_process_debouncing,&mock_process_debouncing);    
    }
    
    void teardown() {
    }
};

// TEST(ButtonEvent, test_press_event)
// {
//     // set p_button_state == BUTTON_OFF
//     int p_button_state = BUTTON_OFF;
//     int button_event = 0; //NOEVT = 0
//     // process debounce and return BUTTON_ON state
//     mock().expectOneCall("process_debouncing").withParameter("button_state",p_button_state).andReturnValue(BUTTON_ON);
//     // get_event(p_button_state, button_state) return PRESSED event
//     button_event = get_event();
//     LONGS_EQUAL(button_event, PRESSED);    
//     // assert event == PRESSED
// }
