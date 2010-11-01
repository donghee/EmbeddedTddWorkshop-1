/*
TODO: 
 X mock plugin 쓰도록 refactoring
 X 디렉토리 정리
 X _button_pressed에서 앞에 _ 빼기
 * led_on/off 구현
  - link-time substitute 이용.
 * is_pressed 단일 테스트
 * 전체 시스템 테스트 (누르면 Led 켜지고, 안누르면 꺼지는지)
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

TEST(Debouncing, test_debouncing)
{
    
}

