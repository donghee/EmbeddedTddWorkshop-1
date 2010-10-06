//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "LightScheduler.h"
#include "LightController.h"

#if 0
//START: SingleEventDataInit1
enum {
    UNUSED = -1,
    TURNOFF, TURNON,
};

typedef struct { //<callout id="co.scheduledLightEventStruct"/>
    int id;
    Day day;
    int minute;
    int event;

} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent; //<callout id="co.scheduledLightEvent"/>

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
//END: SingleEventDataInit1
#endif

//START: MultipleEventData
enum {
    UNUSED = -1,
    TURNOFF, TURNON,
    MAX_EVENTS = 128
};

typedef struct {
    int id;
    Day day;
    int minute;
    int event;

} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];
//END: MultipleEventData


//START: MultipleEventCreate2

void LightScheduler_Create(void)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
//END: MultipleEventCreate1

#if 0 //START: MultipleEventCreate1
static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void)
{
    int i;

    scheduledEvent.id = UNUSED;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
#endif //END: MultipleEventCreate1

//START:  SingleEventDestroyRevised1
void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
//END:  SingleEventDestroyRevised1

//START: ErrorReturns
static int scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    if (id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minute = minute;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minute) //<callout id="co.LightScheduler_ScheduleTurnOn1"/>
{
    return scheduleEvent(id, day, minute, TURNON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minute) //<callout id="co.LightScheduler_ScheduleTurnOff1"/>
{
    return scheduleEvent(id, day, minute, TURNOFF);
}
//END: ErrorReturns



#if 0 //START:  SingleEventDestroy
void LightScheduler_Destroy(void)
{
}
#endif //END:  SingleEventDestroy

#if 0 //START: MultipleEventSchedule1
static void scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++) //<callout id="co.schedMultiple"/>
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minute = minute;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            break;
        }
    }

    if (scheduledEvent.id == UNUSED) //<callout id="co.schedSingle"/>
    {
        scheduledEvent.day = day;
        scheduledEvent.minute = minute;
        scheduledEvent.event = event;
        scheduledEvent.id = id;
    }
}
//END: MultipleEventSchedule1
#endif

#if 0
//START: SingleEventSchedule1
static void scheduleEvent(int id, Day day, int minute, int event) //<callout id="co.scheduleEvent1"/>
{
    if (scheduledEvent.id == UNUSED)
    {
        scheduledEvent.day = day;
        scheduledEvent.minute = minute;
        scheduledEvent.event = event;
        scheduledEvent.id = id;
    }
}
//END: SingleEventSchedule1
#endif

#if 0 //START: MultipleEvent
static void scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minute = minute;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            break;
        }
    }
}
//END: MultipleEvent

//START: SingleEventSchedule1
void LightScheduler_ScheduleTurnOn(int id, Day day, int minute) //<callout id="co.LightScheduler_ScheduleTurnOn1"/>
{
    scheduleEvent(id, day, minute, TURNON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minute) //<callout id="co.LightScheduler_ScheduleTurnOff1"/>
{
    scheduleEvent(id, day, minute, TURNOFF);
}
//END: SingleEventSchedule1
#endif

//START: DoesLightRespondToday2
static int DoesLightRespondToday(Time * time, int reactionDay) //<callout id="co.DoesLightRespondToday2"/>
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return 1;
    if (reactionDay == today)
        return 1;
    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return 1;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return 1;
    return 0;
}
//END: DoesLightRespondToday2

//START: operateLight
static void operateLight(ScheduledLightEvent * lightEvent)
{
    if (lightEvent->event == TURNON)
         LightController_On(lightEvent->id);
    else if (lightEvent->event == TURNOFF)
         LightController_Off(lightEvent->id);

}
//END: operateLight

//START: processEvent2
static void processEventsDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (!DoesLightRespondToday(time, lightEvent->day))
        return;
    if (time->minuteOfDay != lightEvent->minute)
        return;

    operateLight(lightEvent);
}
//END: processEvent2
#if 0 //START: SingleEventWakeup2
void LightScheduler_Wakeup()//<callout id="co.LightScheduler_Wakeup2"/>
{
    Time time;
    TimeService_GetTime(&time);
    if (scheduledEvent.id != UNUSED)
        processEventsDueNow(&time, &scheduledEvent);
}
//END: SingleEventWakeup2
#endif

#if 0 //START: MultipleEventWakeup1
void LightScheduler_Wakeup()
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id != UNUSED)
            processEventsDueNow(&time, &scheduledEvents[i]);
    }

    if (scheduledEvent.id != UNUSED)
        processEventsDueNow(&time, &scheduledEvent);
}
//END: MultipleEventWakeup1
#endif

//START: MultipleEvent3
void LightScheduler_Wakeup()
{
    int i;

    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventsDueNow(&time, &scheduledEvents[i]);
    }
}
//END: MultipleEvent3

#if 0 //START: MultipleEvent2
void LightScheduler_Wakeup()
{
    int i;

    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id != UNUSED)
            processEventsDueNow(&time, &scheduledEvents[i]);
    }
}
#endif //END: MultipleEvent2

#if 0 //START: MultipleEvent1
void LightScheduler_Wakeup()
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id != UNUSED)
            processEventsDueNow(&time, &scheduledEvents[i]);
    }

    if (scheduledEvent.id != UNUSED)
        processEventsDueNow(&time, &scheduledEvent);
}
#endif //END: MultipleEvent1

//START: MultipleEventRemove1
void LightScheduler_ScheduleRemove(int id, Day day, int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == id
         && scheduledEvents[i].day == day
         && scheduledEvents[i].minute == minute)
         {
             scheduledEvents[i].id = UNUSED;
         }
    }
 }
//END: MultipleEventRemove1

#if 0 //START: SingleEventRemove1
void LightScheduler_ScheduleRemove(int id, Day day, int minute)
{
    if (scheduledEvent.id == id
    && scheduledEvent.day == day
    && scheduledEvent.minute == minute)
    {
        scheduledEvent.id = UNUSED;
    }
}
#endif //END: SingleEventRemove1

#if 0
static ScheduledLightEvent scheduledEvent;

//START: DoesLightRespondToday1
static int DoesLightRespondToday(Time * time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return 1;
    if (reactionDay == today)
        return 1;
    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return 1;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return 1;
    return 0;
}
//END: DoesLightRespondToday1

//START: SingleEventWakeup1
static void processEventsDueNow(Time * time, ScheduledLightEvent * lightEvent)
{
    if (!(time, lightEvent->day))
        return;
    if (time->minuteOfDay != lightEvent->minute)
        return;

    if (lightEvent->event == TURNON)
         LightController_On(lightEvent->id);
    else if (lightEvent->event == TURNOFF)
         LightController_Off(lightEvent->id);

}

void LightScheduler_Wakeup()
{
    Time time;
    TimeService_GetTime(&time);

    if (scheduledEvent.id != UNUSED)
        processEventsDueNow(&time, &scheduledEvent);
}
//END: SingleEventWakeup1

#endif

#if 0
static ScheduledLightEvent scheduledEvent;
//START: SingleEventLongMethod
void LightScheduler_ScheduleTurnOn(int id, Day day, int minute)
{
    if (scheduledEvent.id == UNUSED)
    {
        scheduledEvent.day = day;
        scheduledEvent.minute = minute;
        scheduledEvent.event = TURNON;
        scheduledEvent.id = id;
    }
}
//END: SingleEventLongMethod

//START: WakeUpLongMethod
void LightScheduler_Wakeup()
{
    Time time;
    ScheduledLightEvent * lightEvent = &scheduledEvent;
    TimeService_GetTime(&time);

    if (scheduledEvent.id != UNUSED)
    {
        if (time.minuteOfDay != lightEvent->minute)
            return;

        if (lightEvent->event == TURNON)
             LightController_On(lightEvent->id);
        else if (lightEvent->event == TURNOFF)
             LightController_Off(lightEvent->id);


    }
}
//END: WakeUpLongMethod
#endif
