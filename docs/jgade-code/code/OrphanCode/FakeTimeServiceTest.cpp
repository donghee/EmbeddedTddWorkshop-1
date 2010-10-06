#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeTimeService.h"
#include "LightScheduler.h"
#include "memory.h"
}

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
      TimeService_Create();
    }

    void teardown()
    {
       TimeService_Destroy();
    }
};

//START:tests2
static Time savedTime;

static void TestCallback(Time* time)
{
    memcpy(&savedTime, time, sizeof(savedTime));
}

TEST(FakeTimeService, SimulateATic)
{
    TimeService_SetPeriodicAlarmInSeconds(60, TestCallback);

    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_MinuteIsUp();

    LONGS_EQUAL(42, savedTime.minute);
    LONGS_EQUAL(SUNDAY, savedTime.dayOfWeek);
}
//END:tests2

#if 0
//START:tests
TEST(FakeTimeService, Create)
{
    LONGS_EQUAL(TIME_UNKNOWN, TimeService_GetMinute());
    LONGS_EQUAL(TIME_UNKNOWN, TimeService_GetDay());
}

TEST(FakeTimeService, Set)
{
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SUNDAY);
    LONGS_EQUAL(42, TimeService_GetMinute());
    LONGS_EQUAL(SUNDAY, TimeService_GetDay());
}
//END:tests
#endif
