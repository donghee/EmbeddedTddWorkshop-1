//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net

#include "TimeService.h"

//static local variables
static long int theMinute;
static int theDay;

void TimeService_Create(void)
{
    theMinute = -1;
    theDay = -1;
}

void TimeService_Destroy()
{
}

void TimeService_GetTime(Time* time)
{
    time->minuteOfDay = theMinute;
    time->dayOfWeek = theDay;
}

int TimeService_GetMinute(void)
{
    return theMinute;
}

void FakeTimeService_SetMinute(long int minute)
{
    theMinute = minute;
}

void FakeTimeService_SetDay(int day)
{
    theDay = day;
}

int TimeService_GetDay(void)
{
    return theDay;
}

