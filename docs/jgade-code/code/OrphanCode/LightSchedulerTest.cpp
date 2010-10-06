//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net

#if 1

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
#include "FakeLightController.h"
#include "FakeTimeService.h"
#include "RandomMinute.h"
}


TEST_GROUP(LightScheduler)
{
    int id;
    Day fakeDay;
    Day scheduledDay;
    int fakeMinute;
    int scheduledMinute;
    int expectedId;
    int expectedState;

    void setup()
    {
      LightController_Create();
      LightScheduler_Create();

      id = 4;
      fakeDay = MONDAY;
      scheduledDay = NONE;
      fakeMinute = 1234;
      scheduledMinute = 1234;
      expect(NO_ID, UNKNOWN_STATE);
    }

    //START: DestroyCancelsOneMinuteAlarm
    void teardown()
    {
       LightScheduler_Destroy();
       POINTERS_EQUAL(NULL, (void *)FakeTimeSource_GetAlarmCallback());
    }
    //END:DestroyCancelsOneMinuteAlarm

    void expect(int id, int level)
    {
        expectedId = id;
        expectedState = level;
    }

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(NONE, FakeLightController_getLastId());
    LONGS_EQUAL(NONE, FakeLightController_getLastState());
}

//START:CreateStartsOneMinuteAlarm
TEST(LightScheduler, CreateStartsOneMinuteAlarm)
{
    POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                   (void *)FakeTimeSource_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
}

//END:CreateStartsOneMinuteAlarm


/**********
 The first few tests looked like this, then I refactored them
 to remove the duplication.
 */
#if 0
// START: NoChangeToLightsDuringInitialization
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
// END: NoChangeToLightsDuringInitialization

// START: NoScheduleNothingHappens
TEST(LightScheduler, NoScheduleNothingHappens)
{
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
// END: NoScheduleNothingHappens
// START: ScheduleOnTodayNotTimeYet_1
TEST(LightScheduler, ScheduleOnTodayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.sched" />
    FakeTimeService_SetMinute(1199); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.SetTime" />
    LightScheduler_Wakeup();//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.wake" />
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk1" />
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk2" />
}
// END: ScheduleOnTodayNotTimeYet_1
//START: WeekdayScheduleNotOperatedOnSunday
TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
//END: WeekdayScheduleNotOperatedOnSunday
//START: WeekdayScheduleIsOperatedOnMonday
TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}
//END:WeekdayScheduleIsOperatedOnMonday
#endif

#if 0 //START: Conditional
TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 100);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_Wakeup();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(6, WEEKEND, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(6, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
//END:Conditional
#endif

//START: ScheduleTwo
TEST(LightScheduler, ScheduleTwoEventsAtTheSameTIme)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_Wakeup();

    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLightState(3));
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLightState(12));
}
//END: ScheduleTwo

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, 100);

    FakeTimeService_SetMinute(99);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, scheduledMinute);
    FakeTimeService_SetMinute(fakeMinute);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayButItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(TUESDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, TUESDAY, 200);
    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(TUESDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_OFF, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, WEEKEND, 200);

    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(SATURDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_OFF, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(SUNDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 100);

    FakeTimeService_SetMinute(100);
    FakeTimeService_SetDay(SUNDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 200);

    FakeTimeService_SetMinute(200);
    FakeTimeService_SetDay(MONDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);

    FakeTimeService_SetMinute(1000);
    FakeTimeService_SetDay(FRIDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(id, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
    scheduledDay = WEEKDAY;
    fakeDay = SATURDAY;
    scheduledMinute = fakeMinute;
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);

    FakeTimeService_SetMinute(1000);
    FakeTimeService_SetDay(SATURDAY);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(6000);

    LightScheduler_Wakeup();

    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

//START: RemoveMultipleScheduledEvent
TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(7, MONDAY, 600);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(600);

    LightScheduler_Wakeup();

    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
//END: RemoveMultipleScheduledEvent

//START: RejectsTooManyEvents
TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LightScheduler_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LONGS_EQUAL(LightScheduler_Fail_TooManyEvents,
            LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}
//END: RejectsTooManyEvents

//START: CheckLightIds
TEST(LightScheduler, AcceptsValidLightIds)
{
    LONGS_EQUAL(LightScheduler_OK,
                LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    LONGS_EQUAL(LightScheduler_OK,
                LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    LONGS_EQUAL(LightScheduler_OK,
                LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
    LONGS_EQUAL(LightScheduler_Fail_IdOutOfBounds,
                LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    LONGS_EQUAL(LightScheduler_Fail_IdOutOfBounds,
                LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}
//END: CheckLightIds

//START: RemoveRecyclesEventSlot
TEST(LightScheduler, RemoveRecyclesEventSlot)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LightScheduler_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    LONGS_EQUAL(LightScheduler_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}
//END: RemoveRecyclesEventSlot

#if 0
TEST(LightScheduler, MultipleScheduledEventsSameTime)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, 500);
    LightScheduler_ScheduleTurnOn(3, MONDAY, 500);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(500);

    LightScheduler_Wakeup();
    LONGS_EQUAL(2, FakeLightController_getEventCounts());
}
TEST(LightScheduler, MultipleScheduledEventsDifferentTimes)
{
    LightScheduler_ScheduleTurnOff(4, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(3, MONDAY, 500);

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(500);

    LightScheduler_Wakeup();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());

    FakeTimeService_SetMinute(600);

    LightScheduler_Wakeup();
    LONGS_EQUAL(4, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_OFF, FakeLightController_getLastState());
}

static int randomMinute;
static int FakeRandomMinute_Get()
{
    if (randomMinute > 30)
        randomMinute = -30;
    return randomMinute++;
}


TEST(LightScheduler, EnableRandomizeEarly)
{
    UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    randomMinute = -10;

    LightScheduler_ScheduleTurnOnRandomize(4, EVERYDAY, 600);

    FakeTimeService_SetMinute(590);

    LightScheduler_Wakeup();
    LONGS_EQUAL(4, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}

TEST(LightScheduler, EnableRandomizeEarlyOnlyOneEventFires)
{
    UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    randomMinute = -10;

    LightScheduler_ScheduleTurnOnRandomize(4, EVERYDAY, 600);

    FakeTimeService_SetMinute(590);
    LightScheduler_Wakeup();
    LightController_Create();
    FakeTimeService_SetMinute(591);
    LightScheduler_Wakeup();

    LONGS_EQUAL(NONE, FakeLightController_getLastId());
}
#endif


#else

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "FakeLightController.h"
#include "FakeTimeService.h"
#include "RandomMinute.h"
}

static void (*scheduler)(int id, Day day, int minute);


TEST_GROUP(LightScheduler)
{
    int id;
    Day fakeDay;
    Day scheduledDay;
    int fakeMinute;
    int scheduledMinute;
    int expectedId;
    int expectedState;

    void setup()
    {
      LightController_Create();
      LightScheduler_Create();

      scheduler = 0;
      id = 4;
      fakeDay = MONDAY;
      scheduledDay = NONE;
      fakeMinute = 1234;
      scheduledMinute = 1234;
      expect(NO_ID, UNKNOWN_STATE);
    }

    //START: DestroyCancelsOneMinuteAlarm
    void teardown()
    {
       LightScheduler_Destroy();
       POINTERS_EQUAL(NULL, (void*)FakeTimeSource_GetAlarmCallback());
    }
    //END:DestroyCancelsOneMinuteAlarm

    void doTest()
    {
        CHECK(0 != scheduler);

        scheduler(id, scheduledDay, scheduledMinute);

        FakeTimeService_SetMinute(fakeMinute);
        FakeTimeService_SetDay(fakeDay);
        FakeTimeService_MinuteIsUp();
        LONGS_EQUAL(expectedId, FakeLightController_getLastId());
        LONGS_EQUAL(expectedState, FakeLightController_getLastState());
    }

    void expect(int id, int level)
    {
        expectedId = id;
        expectedState = level;
    }

};

TEST(LightScheduler, CreateDoesNotChangeTheLights)
{
    LONGS_EQUAL(NONE, FakeLightController_getLastId());
    LONGS_EQUAL(NONE, FakeLightController_getLastState());
}

//START:CreateStartsOneMinuteAlarm
TEST(LightScheduler, CreateStartsOneMinuteAlarm)
{
    POINTERS_EQUAL((void*)LightScheduler_Wakeup,
                   (void*)FakeTimeSource_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
}

//END:CreateStartsOneMinuteAlarm


/**********
 The first few tests looked like this, then I refactored them
 to remove the duplication.
 */
#if 0
// START: NoChangeToLightsDuringInitialization
TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
// END: NoChangeToLightsDuringInitialization

// START: NoScheduleNothingHappens
TEST(LightScheduler, NoScheduleNothingHappens)
{
    LightScheduler_Wakeup();
    LONGS_EQUAL(-1, FakeLightController_getLastId());
    LONGS_EQUAL(-1, FakeLightController_getLastState());
}
// END: NoScheduleNothingHappens
// START: ScheduleOnTodayNotTimeYet_1
TEST(LightScheduler, ScheduleOnTodayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.sched" />
    FakeTimeService_SetMinute(1199); //<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.SetTime" />
    LightScheduler_Wakeup();//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.wake" />
    LONGS_EQUAL(-1, FakeLightController_getLastId());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk1" />
    LONGS_EQUAL(-1, FakeLightController_getLastState());//<callout id="co.LightScheduler.ScheduleOnTodayNotTimeYet_1.chk2" />
}
// END: ScheduleOnTodayNotTimeYet_1
//START: WeekdayScheduleNotOperatedOnSunday
TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(-1, FakeLightController_getLastId());
    LONGS_EQUAL(-1, FakeLightController_getLastState());
}
//END: WeekdayScheduleNotOperatedOnSunday
//START: WeekdayScheduleIsOperatedOnMonday
TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
}
//END:WeekdayScheduleIsOperatedOnMonday
#endif

#if 0 //START: Conditional
TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 100);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_Wakeup();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(6, WEEKEND, 1200);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(6, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
//END:Conditional
#endif

#if 0 //START: refactorThis
TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(3, WEEKEND, 100);
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(100);
    FakeTimeService_MinuteIsUp();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(0, FakeLightController_getLastState());
}
//END: refactorThis
#endif

//START: rambleOn
TEST(LightScheduler, ScheduleWeekEnd)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    FakeTimeService_SetDay(FRIDAY);
    FakeTimeService_SetMinute(1200);
    FakeTimeService_MinuteIsUp();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
    FakeTimeService_SetDay(SATURDAY);
    FakeTimeService_SetMinute(1200);
    FakeTimeService_MinuteIsUp();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
    LightController_Off(3);
    FakeTimeService_SetDay(SUNDAY);
    FakeTimeService_SetMinute(1200);
    FakeTimeService_MinuteIsUp();
    LONGS_EQUAL(3, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
    LightController_Create();
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    FakeTimeService_MinuteIsUp();
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}
//END: rambleOn

#endif
