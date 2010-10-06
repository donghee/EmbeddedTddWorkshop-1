//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_TimeService_H
#define D_TimeService_H

//START: TimeStruct
enum {TS_SUNDAY=1};

typedef struct Time
{
    int minute;
    int dayOfWeek;
} Time;
//END: TimeStruct

//START: pushModel
void TimeService_Create(void);
void TimeService_Destroy(void);

typedef void (*WakeupCallback)(Time*);

void TimeService_SetPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);

void TimeService_CancelPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);
//END: pushModel

#if 0 //START: original
void TimeService_Create(void);
void TimeService_Destroy(void);

int TimeService_GetMinute(void);
int TimeService_GetDay(void);

typedef void (*WakeupCallback)(void);
void TimeService_SetPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);

void TimeService_CancelPeriodicAlarmInSeconds(
        int seconds, WakeupCallback);
//END: original
#endif

#endif  // D_TimeService_H
