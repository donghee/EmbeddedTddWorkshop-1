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

    #if 0 //START: helpers_1
     void whenItBecomes(int day, int minute)
     {
         FakeTimeService_SetDay(day);
         FakeTimeService_SetMinute(minute);
         LightScheduler_Wakeup();
     }
     void thenExpect(int id, int level)
     {
         LONGS_EQUAL(id, FakeLightController_getLastId());
         LONGS_EQUAL(level, FakeLightController_getLastState());
     }
     #endif //END: helpers_1
     void whenItBecomes(int day, int minute)
     {
         FakeTimeService_SetDay(day);
         FakeTimeService_SetMinute(minute);
         LightScheduler_Wakeup();
     }
     //START: helpers_2
      void thenExpect(int id, int level)
      {
          if (id == NO_ID)
          {
              LONGS_EQUAL(id, FakeLightController_getLastId());
              LONGS_EQUAL(level, FakeLightController_getLastState());
          }
          else
              LONGS_EQUAL(level, FakeLightController_getLightState(id));
      }
      //END: helpers_2

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

//START: Conditional
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
//END: Conditional

#if 0 //START: ScheduleWeekEndItsMonday_2
TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    whenItBecomes(MONDAY, 1200);
    thenExpect(NO_ID, UNKNOWN_STATE);
}
#endif //END: ScheduleWeekEndItsMonday_2

//START: ScheduleTwo
TEST(LightScheduler, ScheduleTwoEventsAtTheSameTIme)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

    whenItBecomes(SUNDAY, 1200);

    thenExpect(3, LIGHT_ON);
    thenExpect(12, LIGHT_ON);
}
//END: ScheduleTwo

TEST(LightScheduler, ScheduleEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, 100);
    whenItBecomes(SUNDAY, 1200);
    thenExpect(NO_ID, UNKNOWN_STATE);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(id, EVERYDAY, scheduledMinute);
    whenItBecomes(SUNDAY, scheduledMinute);
    thenExpect(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsNotTuesdayButItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    whenItBecomes(MONDAY, 100);
    thenExpect(NO_ID, UNKNOWN_STATE);
}

TEST(LightScheduler, ScheduleOnTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, TUESDAY, 100);
    whenItBecomes(TUESDAY, 100);
    thenExpect(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffTuesdayAndItsTuesdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, TUESDAY, 200);
    whenItBecomes(TUESDAY, 200);
    thenExpect(id, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleOffWeekendAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOff(id, WEEKEND, 200);
    whenItBecomes(SATURDAY, 200);
    thenExpect(id, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);

    whenItBecomes(SUNDAY, 100);
    thenExpect(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekendAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKEND, 100);
    whenItBecomes(MONDAY, 100);
    thenExpect(id, UNKNOWN_STATE);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSundayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 100);
    whenItBecomes(SUNDAY, 100);
    thenExpect(NO_ID, UNKNOWN_STATE);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsMondayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 200);
    whenItBecomes(MONDAY, 200);
    thenExpect(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsFridayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);
    whenItBecomes(FRIDAY, 1000);
    thenExpect(id, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOnWeekdayAndItsSaturdayAndItsTime)
{
    LightScheduler_ScheduleTurnOn(id, WEEKDAY, 1000);
    whenItBecomes(SATURDAY, 1000);
    thenExpect(NO_ID, UNKNOWN_STATE);
}

TEST(LightScheduler, RemoveScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    whenItBecomes(MONDAY, 599);
    thenExpect(NO_ID, UNKNOWN_STATE);
}

//START: RemoveMultipleScheduledEvent
TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);

    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    LightScheduler_ScheduleRemove(7, MONDAY, 600);

    whenItBecomes(MONDAY, 600);
    thenExpect(NO_ID, UNKNOWN_STATE);
}
//END: RemoveMultipleScheduledEvent

//START: RejectsTooManyEvents
TEST(LightScheduler, RejectsTooManyEvents)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LONGS_EQUAL(LS_TOO_MANY_EVENTS,
                LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}
//END: RejectsTooManyEvents

//START: CheckLightIds
TEST(LightScheduler, AcceptsValidLightIds)
{
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    LONGS_EQUAL(LS_ID_OUT_OF_BOUNDS,
                LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}
//END: CheckLightIds

//START: RemoveRecyclesEventSlot
TEST(LightScheduler, RemoveRecyclesEventSlot)
{
    int i;
    for (i = 0; i < 128; i++)
        LONGS_EQUAL(LS_OK,
                    LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    LONGS_EQUAL(LS_OK,
                LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}
//END: RemoveRecyclesEventSlot

