//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightDriverSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}

TEST_GROUP(LightScheduler)
{
    int scheduledMinute;
    int expectedId;
    int expectedLevel;
    int lightNumber;
    int seed;
    int pseudoRandomIncrement;


    void setup()
    {
		LightController_Create();
		LightDriverSpy_Reset();
		LightDriverSpy_AddSpiesToController();
		LightScheduler_Create();

		scheduledMinute = 1234;
		expect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
		lightNumber = 4;

		UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
		FakeRandomMinute_Reset();
		seed = -10;
		pseudoRandomIncrement = 5;
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }

    void wakeupAndCheck()
    {
        LightScheduler_TimeToCheckTheSchedule();

        LONGS_EQUAL(expectedId, LightDriverSpy_GetLastId());
        LONGS_EQUAL(expectedLevel, LightDriverSpy_GetLastState());
    }

    void setNow(int day, int minute)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minute);
    }

    void expect(int id, int level)
    {
        expectedId = id;
        expectedLevel = level;
    }

    void whenItBecomes(int day, int minute)
    {
    	setNow(day, minute);
    	wakeupAndCheck();
    }

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(NO_LIGHT_ID, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetLastState());
}

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    expect(NO_LIGHT_ID,LIGHT_STATE_UNKNOWN);
    whenItBecomes(MONDAY, scheduledMinute-1);
}

TEST(LightScheduler, ScheduleOnTodayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, scheduledMinute);
    expect(3, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    expect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
    whenItBecomes(MONDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, scheduledMinute);
    expect(3, LIGHT_ON);
    whenItBecomes(TUESDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(lightNumber, TUESDAY, scheduledMinute);
    expect(lightNumber, LIGHT_OFF);
    whenItBecomes(TUESDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
	LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
	expect(lightNumber, LIGHT_OFF);
	whenItBecomes(SATURDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	expect(lightNumber, LIGHT_ON);
	whenItBecomes(SUNDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOff(lightNumber, WEEKEND, scheduledMinute);
	expect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
	whenItBecomes(MONDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKEND, scheduledMinute);
	expect(lightNumber, LIGHT_ON);
	whenItBecomes(SUNDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	expect(lightNumber, LIGHT_ON);
	whenItBecomes(MONDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	expect(lightNumber, LIGHT_ON);
	whenItBecomes(FRIDAY, scheduledMinute);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
	LightScheduler_ScheduleTurnOn(lightNumber, WEEKDAY, scheduledMinute);
	expect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
	whenItBecomes(SATURDAY, scheduledMinute);
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, scheduledMinute);
    LightScheduler_ScheduleRemove(6, MONDAY, scheduledMinute);

	expect(NO_LIGHT_ID, LIGHT_STATE_UNKNOWN);
	whenItBecomes(MONDAY, scheduledMinute);
}

TEST(LightScheduler, MultipleScheduledEventsSameTime)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute);
    setNow(MONDAY, scheduledMinute);

    LightScheduler_TimeToCheckTheSchedule();

    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(4));
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(3));
}

TEST(LightScheduler, MultipleScheduledEventsDifferentTimes)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOn(3, MONDAY, scheduledMinute+1);

    expect(4, LIGHT_OFF);
    whenItBecomes(MONDAY, scheduledMinute);

    expect(3, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute+1);
}
TEST(LightScheduler, EnableRandomize)
{
	FakeRandomMinute_SetSeedAndIncrement(seed, 1);
    LightScheduler_ScheduleTurnOnRandomize(lightNumber, EVERYDAY, scheduledMinute);

    expect(lightNumber, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute + seed);
}

TEST(LightScheduler, DifferentRandmomFactorTheSecondDay)
{
	FakeRandomMinute_SetSeedAndIncrement(seed, 1);

    LightScheduler_ScheduleTurnOnRandomize(lightNumber, EVERYDAY, scheduledMinute);

    expect(lightNumber, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute + seed);
}

TEST(LightScheduler, MultipleRandomControls)
{
	FakeRandomMinute_SetSeedAndIncrement(seed, 5);

    LightScheduler_ScheduleTurnOnRandomize(lightNumber, EVERYDAY, scheduledMinute);
    LightScheduler_ScheduleTurnOnRandomize(lightNumber+1, EVERYDAY, scheduledMinute+3);

    expect(lightNumber, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute + seed);
    expect(lightNumber+1, LIGHT_ON);
    whenItBecomes(MONDAY, scheduledMinute +seed + 3 + 5);
}

