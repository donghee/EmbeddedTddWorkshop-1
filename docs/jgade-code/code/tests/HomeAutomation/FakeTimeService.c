//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "FakeTimeService.h"
#include "CppUTest/TestHarness_c.h"

//static local variables
static Time fakeTime;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
    fakeTime.minuteOfDay = -1;
    fakeTime.dayOfWeek = -1;
    callback = 0;
    period = -1;
}

void TimeService_Destroy(void)
{
}

//START: interestingParts
void FakeTimeService_MinuteIsUp()
{
    CHECK_C(callback != 0);  //<callout id="co.FakeTimeService.checkNotNull" />
    callback(&fakeTime); //<callout id="co.FakeTimeService.callback" />
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)//<callout id="co.FakeTimeService.set" />
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds( //<callout id="co.FakeTimeService.cancel" />
        int seconds, WakeupCallback cb)
{
    callback = 0;
    period = 0;
}
//END: interestingParts

void TimeService_GetTime(Time * time)
{
    time->minuteOfDay = fakeTime.minuteOfDay;
    time->dayOfWeek = fakeTime.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute)
{
    fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
    fakeTime.dayOfWeek = day;
}

WakeupCallback FakeTimeSource_GetAlarmCallback()
{
    return callback;
}

int FakeTimeSource_GetAlarmPeriod()
{
    return period;
}

