//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

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

