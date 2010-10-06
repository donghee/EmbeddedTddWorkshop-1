//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


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
    MAX_EVENTS = 128, UNUSED = -1
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

//START: readyToMove
BOOL TimeService_MatchesDayOfWeek(Time* time, Day day)
{
    int today = time->dayOfWeek;

    if (day == EVERYDAY)
        return TRUE;
    if (day == today)
        return TRUE;
    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}
//END: readyToMove

//START: delegate
static BOOL matchesDay(Time* time, ScheduledLightEvent * event)
{
    return TimeService_MatchesDayOfWeek(time, event->day);
}
//END: delegate

#if 0
//START: extracted
static BOOL matchesDay(Time* time, ScheduledLightEvent * event)
{
    int today = time->dayOfWeek;
    Day day = event->day;

    if (day == EVERYDAY)
    return TRUE;
    if (day == today)
    return TRUE;
    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
    return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
    return TRUE;
    return FALSE;
}
//END: extracted
#endif
//START: extracted

static void operateLight(ScheduledLightEvent* lightEvent)
{
    if (TURNON == lightEvent->event)
        LightController_TurnOn(lightEvent->id);
    else if (TURNOFF == lightEvent->event)
        LightController_TurnOff(lightEvent->id);
}

static void resetRandomize(ScheduledLightEvent* e)
{
    if (e->randomize == RANDOM_ON)
        e->randomMinutes = RandomMinute_Get();
    else
        e->randomMinutes = 0;
}

static BOOL eventIsReadyToExecute(Time * time, ScheduledLightEvent * event)
{
    int minute = time->minuteOfDay;

    if (event->id == UNUSED)
        return FALSE;
    if (!matchesDay(time, event))
        return FALSE;
    if (minute != event->minute + event->randomMinutes)
        return FALSE;
    return TRUE;
}
//END: extracted


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

#if 0 //START: betterNames
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                //its the right day
                if (minute == event->minute + event->randomMinutes)
                {
                    if (TURNON == event->event)
                    LightController_TurnOn(event->id);
                    else if (TURNOFF == event->event)
                    LightController_TurnOff(event->id);

                    if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                    else
                    event->randomMinutes = 0;

                }
            }
        }
    }
}
//END: betterNames
#endif

#if 0 //START: NeedsRefactoring2
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                //its the right day
                if (minute == event->minute + event->randomMinutes)
                {
                    if (TURNON == event->event)
                    LightController_TurnOn(event->id);
                    else if (TURNOFF == event->event)
                    LightController_TurnOff(event->id);

                    if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                    else
                    event->randomMinutes = 0;
                }
            }
        }
    }
}
//END: NeedsRefactoring2
#endif

#if 0 //START: NeedsRefactoring2IWish
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        //if (eventIsReadyToExecute()
        //  operateLight();
        ScheduledLightEvent* event = &eventList[i];
        if (event->id != UNUSED)
        {
            Day day = event->day;
            //if (matchesDay())
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            {
                //its the right day
                if (minute == event->minute + event->randomMinutes)
                {
                    //operateLight();
                    if (TURNON == event->event)
                    LightController_TurnOn(event->id);
                    else if (TURNOFF == event->event)
                    LightController_TurnOff(event->id);

                    //resetRandomize()
                    if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                    else
                    event->randomMinutes = 0;
                }
            }
        }
    }
}
//END: NeedsRefactoring2IWish
#endif

#if 0
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        //if (eventIsReadyToExecute()
        //  operateLight();
        ScheduledLightEvent* event = &eventList[i];
        if (event->id != UNUSED)
        {
            //START: NeedsRefactoring2IWishRefined
            //if (matchesDay(time, event))
            Day day = event->day;
            if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                            (SATURDAY == today || SUNDAY == today)) ||
                    (day == WEEKDAY && (today >= MONDAY
                                    && today <= FRIDAY)))
            //END: NeedsRefactoring2IWishRefined

            {
                //its the right day
                if (minute == event->minute + event->randomMinutes)
                {
                    //operateLight(event);
                    if (TURNON == event->event)
                    LightController_TurnOn(event->id);
                    else if (TURNOFF == event->event)
                    LightController_TurnOff(event->id);

                    //resetRandomize(event);
                    if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                    else
                    event->randomMinutes = 0;

                }
            }
        }
    }
}
#endif

#if 0 //START: NeedsRefactoring2IWishPlus2Extracts
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* event = &eventList[i];
        //if (eventIsReadyToExecute(&time, event)
        //  operateLight(event);
        if (event->id != UNUSED)
        {
            if (matchesDay(&time, event))
            {
                //its the right day
                if (minute == event->minute + event->randomMinutes)
                {
                    operateLight(event);
                    resetRandomize(event);
                }
            }
        }
    }
}
//END: NeedsRefactoring2IWishPlus2Extracts
#endif

#if 0 //START: preparing
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);
    Day today = time.dayOfWeek;
    int minute = time.minuteOfDay;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* event = &eventList[i];
        //if (eventIsReadyToExecute(&time, event)
        //  operateLight(event);
        //  resetRandomize(event);
        if (event->id == UNUSED)
        continue;
        if (!matchesDay(&time, event))
        continue;
        if (minute == event->minute + event->randomMinutes)
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
//END: preparing
#endif

//START: processEvent
void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (eventIsReadyToExecute(time, event))
    {
        operateLight(event);
        resetRandomize(event);
    }
}
//END processEvent

#if 1 //START: refactored2
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventsDueNow(&time, &eventList[i]);
    }
}
#endif //END: refactored2

#if 0 //START: refactored1
void LightScheduler_WakeUp(void)
{
    int i;
    Time time;

    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent* event = &eventList[i];
        if (eventIsReadyToExecute(&time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif //END: refactored1

#if 0
//START: quickswap
#if 0
Day day = event->day;
if (!(day == EVERYDAY || day == today
                ||(day == WEEKEND && (SATURDAY == today
                                || SUNDAY == today)) || (day == WEEKDAY
                        && today >= MONDAY && today <= FRIDAY)))
return;
#else
if (!matchesToday(event))
return;
#endif
//END: quickswap
#endif

