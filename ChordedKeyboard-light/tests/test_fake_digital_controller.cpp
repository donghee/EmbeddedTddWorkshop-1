#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "fake_digital_controller.h"
}

TEST_GROUP(FakeDigitalController)
{
    
    void setup() {
        digitalPinSetting();
    }

    void teardown() {
    }

};


TEST(FakeDigitalController, fake_digitalWrite_1_HIGH)
{
    fake_digitalWrite(1, HIGH);
    LONGS_EQUAL(HIGH, digitalRead(1));
}

TEST(FakeDigitalController, TestInitial)
{
    LONGS_EQUAL(LOW, digitalRead(1));        
    LONGS_EQUAL(LOW, digitalRead(2));    
}

TEST(FakeDigitalController, fake_three_digitalWrite_LOW_HIGH_LOW)
{
    fake_digitalWrite(1, LOW);
    fake_digitalWrite(2, HIGH);
    fake_digitalWrite(3, LOW);    
    LONGS_EQUAL(LOW, digitalRead(1));        
    LONGS_EQUAL(HIGH, digitalRead(2));
    LONGS_EQUAL(LOW, digitalRead(3));        
}
