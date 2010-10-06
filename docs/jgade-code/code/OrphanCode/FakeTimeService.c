#include "FakeTimeService.h"
#include "CppUTest/TestHarness_c.h"

//static local variables
static Time time;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
    time.minute = -1;
    time.dayOfWeek = -1;
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
    callback(&time); //<callout id="co.FakeTimeService.callback" />
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

void FakeTimeService_SetMinute(int minute)
{
    time.minute = minute;
}

void FakeTimeService_SetDay(int day)
{
    time.dayOfWeek = day;
}

WakeupCallback FakeTimeSource_GetAlarmCallback()
{
    return callback;
}

int FakeTimeSource_GetAlarmPeriod()
{
    return period;
}

