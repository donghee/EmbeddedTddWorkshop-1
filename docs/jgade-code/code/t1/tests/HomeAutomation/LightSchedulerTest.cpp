//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "LightScheduler.h"
#include "LightDriverSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    int scheduledMinute;
    int expectedId;
    int expectedLevel;
    int lightNumber;
    int firstRandomMinute;

    #if 0 //START: manualPtrInitRestore
    int (*savedRandomMinute_Get)();

    void setup()
    {
        //other setup code
        savedRandomMinute_Get = RandomMinute_Get;
        RandomMinute_Get = FakeRandomMinute_Get;
    }

    void teardown()
    {
        //other teardown code
        RandomMinute_Get = savedRandomMinute_Get;
    }
    //END: manualPtrInitRestore
    #endif

    #if 0 //START: UT_PTR_SET
    void setup()
    {
        //other setup code
        UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    }

    void teardown()
    {
        //other teardown code
    }
    //END: UT_PTR_SET
    #endif

    void setup()
    {
		LightController_Create();
		LightDriverSpy_Reset();
		LightDriverSpy_AddAllToController();
		LightScheduler_Create();

		scheduledMinute = 1234;
		thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
		lightNumber = 4;

		UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
		FackRandomMinute_Reset();
		firstRandomMinute = -10;
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }

    //START: helpers
    void whenItBecomes(int day, int minute)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minute);
        LightScheduler_WakeUp();
    }

    void thenExpect(int id, int level)
    {
        LONGS_EQUAL(id, LightDriverSpy_GetLastId());
        LONGS_EQUAL(level, LightDriverSpy_GetLastState());
    }
    //END: helpers

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(NO_LIGHT_ID, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetLastState());
}

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    whenItBecomes(MONDAY, scheduledMinute-1);
    thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTodayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    whenItBecomes(MONDAY, scheduledMinute);
    thenExpect(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    whenItBecomes(MONDAY, scheduledMinute);
    thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    whenItBecomes(TUESDAY, scheduledMinute);
    thenExpect(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(lightNumber, TUESDAY, scheduledMinute);
    whenItBecomes(TUESDAY, scheduledMinute);
    thenExpect(lightNumber, LIGHT_OFF);
}

//START: refactored
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
    whenItBecomes(SATURDAY, scheduledMinute);
    thenExpect(lightNumber, LIGHT_OFF);
}
//END: refactored

#if 0 //START: GivWenZen
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAtTheScheduledTime)
{
    given(lightNumber); isScheduledFor(WEEKEND); toTurnOffAt(scheduledMinute);
    whenItBecomes(SATURDAY); at(scheduledMinute);
    then(lightNumber); is(LIGHT_OFF);
}
#endif //END: GivWenZen

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	whenItBecomes(SUNDAY, scheduledMinute);
	thenExpect(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
	whenItBecomes(MONDAY, scheduledMinute);
	thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	whenItBecomes(SUNDAY, scheduledMinute);
	thenExpect(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	whenItBecomes(MONDAY, scheduledMinute);
	thenExpect(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	whenItBecomes(FRIDAY, scheduledMinute);
	thenExpect(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	whenItBecomes(SATURDAY, scheduledMinute);
	thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, scheduledMinute);
    LightScheduler_ScheduleRemove(6, MONDAY, scheduledMinute);

	whenItBecomes(MONDAY, scheduledMinute);
	thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, MultipleScheduledEventsSameTime)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute);

    whenItBecomes(MONDAY, scheduledMinute);

    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(4));
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(3));
}

TEST(LightScheduler, MultipleScheduledEventsDifferentTimes)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute+1);

    whenItBecomes(MONDAY, scheduledMinute);
    thenExpect(4, LIGHT_OFF);

    whenItBecomes(MONDAY, scheduledMinute+1);
    thenExpect(3, LIGHT_ON);
}

//START: EnableRandomize
TEST(LightScheduler, EnableRandomize)
{
    FakeRandomMinute_SetFirstAndIncrement(10, 1);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);

    whenItBecomes(MONDAY, scheduledMinute);
    thenExpect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);

    whenItBecomes(MONDAY, scheduledMinute + 10);
    thenExpect(lightNumber, LIGHT_ON);
}
//END: EnableRandomize

TEST(LightScheduler, DifferentRandmomFactorTheSecondDay)
{
	FakeRandomMinute_SetFirstAndIncrement(firstRandomMinute, 1);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);

    whenItBecomes(MONDAY, scheduledMinute + firstRandomMinute);
    thenExpect(lightNumber, LIGHT_ON);
}

TEST(LightScheduler, MultipleRandomControls)
{
	FakeRandomMinute_SetFirstAndIncrement(firstRandomMinute, 5);

    LightScheduler_ScheduleTurnOn(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_Randomize(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(lightNumber+1, EVERYDAY, scheduledMinute+3);
    LightScheduler_Randomize(lightNumber+1, EVERYDAY, scheduledMinute+3);

    whenItBecomes(MONDAY, scheduledMinute + firstRandomMinute);
    thenExpect(lightNumber, LIGHT_ON);

    whenItBecomes(MONDAY, scheduledMinute +firstRandomMinute + 3 + 5);
    thenExpect(lightNumber+1, LIGHT_ON);
}

