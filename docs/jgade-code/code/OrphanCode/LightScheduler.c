//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#if 1


#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"
#include "RandomMinute.h"
#include <stdlib.h>
#include <string.h>

enum
{
    TURNON, TURNOFF, DIM, RANDOM_ON, RANDOM_OFF
};

enum
{
    MAX_EVENTS = 64, UNUSED = -1
};

typedef struct
{
    int id;
    Day day;
    long int minute;
    int event;
    int randomize;
    int randomMinutes;

} ScheduledLightEvent;

static ScheduledLightEvent eventList[MAX_EVENTS];

void LightScheduler_Create()
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        eventList[i].id = UNUSED;
    }
}

void LightScheduler_Destroy()
{
}

static void resetRandomize(ScheduledLightEvent* e);

static void scheduleEvent(int id, Day day, long int minute, int event,
        int randomize)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == UNUSED)
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minute = minute;
            eventList[i].event = event;
            eventList[i].randomize = randomize;
            resetRandomize(&eventList[i]);
            break;
        }
    }
}

void LightScheduler_ScheduleTurnOn(int id, Day day, long int minute)
{
    scheduleEvent(id, day, minute, TURNON, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOff(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNOFF, RANDOM_OFF);
}

void LightScheduler_Randomize(int id, Day day, long int minute)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* e = &eventList[i];
        if (e->id == id && e->day == day && e->minute == minute)
        {
            e->randomize = RANDOM_ON;
            resetRandomize(e);
        }
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, long int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id && eventList[i].day == day
                && eventList[i].minute == minute)
        {
            eventList[i].id = UNUSED;
        }
    }
}



#if 0 //START: NeedsRefactoring1
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day td = time.dayOfWeek;
    int min = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* se = &eventList[i];
        if (se->id != UNUSED)
        {
            Day d = se->day;
            if ( (d == EVERYDAY) || (d == td) || (d == WEEKEND &&
                            (SATURDAY == td || SUNDAY == td)) ||
                    (d == WEEKDAY && (td >= MONDAY
                                    && td <= FRIDAY)))
            {
                //its the right day
                if (min == se->minute + se->randomMinutes)
                {
                    if (TURNON == se->event)
                    LightController_TurnOn(se->id);
                    else if (TURNOFF == se->event)
                    LightController_TurnOff(se->id);

                    if (se->randomize == RANDOM_ON)
                    se->randomMinutes = RandomMinute_Get();
                    else
                    se->randomMinutes = 0;

                }
            }
        }
    }
}
//END: NeedsRefactoring1

#endif



/////////////////////////////////
#else

#include "LightScheduler.h"
#include "LightController.h"
#include "LightSwitch.h"


void LightSwitch_TurnOn(LightSwitch* ls)
{
	ls->TurnOn(ls);
}

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


static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];
//END: MultipleEventData


//START: MultipleEventCreate1
void LightScheduler_Create(void)
{
    int i;

    scheduledEvent.id = UNUSED;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
//END: MultipleEventCreate1

#if 0 //START:  SingleEventDestroy
void LightScheduler_Destroy(void)
{
}
#endif //END:  SingleEventDestroy

//START:  SingleEventDestroyRevised1
void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}
//END:  SingleEventDestroyRevised1

#if 0 //START: MultipleEventSchedule1
static void scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++) //<callout id="co.schedMultiple"/>
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].id = id;
            scheduledEvents[i].day = day;
            scheduledEvents[i].minute = minute;
            scheduledEvents[i].event = event;
            break;
        }
    }

    if (scheduledEvent.id == UNUSED) //<callout id="co.schedSingle"/>
    {
        scheduledEvent.id = id;
        scheduledEvent.day = day;
        scheduledEvent.minute = minute;
        scheduledEvent.event = event;
    }
}
//END: MultipleEventSchedule1
#endif

//START: MultipleEvent
static void scheduleEvent(int id, Day day, int minute, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].id = id;
            scheduledEvents[i].day = day;
            scheduledEvents[i].minute = minute;
            scheduledEvents[i].event = event;
            break;
        }
    }
}
//END: MultipleEvent


#if 0
//START: SingleEventSchedule1
static void scheduleEvent(int id, Day day, int minute, int event) //<callout id="co.scheduleEvent1"/>
{
    if (scheduledEvent.id == UNUSED)
    {
        scheduledEvent.id = id;
        scheduledEvent.day = day;
        scheduledEvent.minute = minute;
        scheduledEvent.event = event;
    }
}
//END: SingleEventSchedule1
#endif
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

//START: DoesLightRespondToday2
static int DoesLightRespondToday(Time* time, int reactionDay) //<callout id="co.DoesLightRespondToday2"/>
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

//START: SingleEventWakeup2
static void checkEvent(Time* time, ScheduledLightEvent* lightEvent)//<callout id="co.checkEvent2"/>
{
    if (!DoesLightRespondToday(time, lightEvent->day))
        return;
    if (time->minute != lightEvent->minute)
        return;

    if (TURNON == lightEvent->event)
         LightController_On(lightEvent->id);
    else if (TURNOFF == lightEvent->event)
         LightController_Off(lightEvent->id);

}
//END: SingleEventWakeup2
#if 0
//START: SingleEventWakeup2
void LightScheduler_Wakeup(Time* time)//<callout id="co.LightScheduler_Wakeup2"/>
{

    if (scheduledEvent.id != UNUSED)
        checkEvent(time, &scheduledEvent);
}
//END: SingleEventWakeup2
#endif

#if 0 //START: MultipleEventWakeup1
void LightScheduler_Wakeup(Time* time)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id != UNUSED)
            checkEvent(time, &scheduledEvents[i]);
    }

    if (scheduledEvent.id != UNUSED)
        checkEvent(time, &scheduledEvent);
}
//END: MultipleEventWakeup1
#endif

//START: MultipleEvent
void LightScheduler_Wakeup(Time* time)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id != UNUSED)
            checkEvent(time, &scheduledEvents[i]);
    }

    if (scheduledEvent.id != UNUSED)
        checkEvent(time, &scheduledEvent);
}
//END: MultipleEvent

//START: SingleEventRemove1
void LightScheduler_ScheduleRemove(int id, Day day, int minute)
{
    if (scheduledEvent.id == id
    && scheduledEvent.day == day
    && scheduledEvent.minute == minute)
    {
        scheduledEvent.id = UNUSED;
    }
}
//END: SingleEventRemove1

#if 0
//START: DoesLightRespondToday1
static int DoesLightRespondToday(int reactionDay)
{
    int today = TimeService_GetDay();

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
static void checkEvent(ScheduledLightEvent* lightEvent)//<callout id="co.checkEvent1"/>
{
    if (!DoesLightRespondToday(lightEvent->day))
        return;
    if (TimeService_GetMinute() != lightEvent->minute)
        return;

    if (TURNON == lightEvent->event)
         LightController_On(lightEvent->id);
    else if (TURNOFF == lightEvent->event)
         LightController_Off(lightEvent->id);

}

void LightScheduler_Wakeup(void)//<callout id="co.LightScheduler_Wakeup1"/>
{
    if (scheduledEvent.id != UNUSED)//<callout id="co.LightScheduler_Wakeup1.chk"/>
        checkEvent(&scheduledEvent);
}
//END: SingleEventWakeup1

#endif
#endif
