//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_TimeService_H
#define D_TimeService_H

//START: interface
typedef struct Time
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time *);

typedef void (*WakeupCallback)();

void TimeService_SetPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);

void TimeService_CancelPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);
//END: interface


#endif  // D_TimeService_H
