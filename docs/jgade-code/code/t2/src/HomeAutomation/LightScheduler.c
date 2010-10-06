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
    ScheduledLightEvent* event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        event->id = UNUSED;
    }
}

void LightScheduler_Destroy()
{
}

static void resetRandomize(ScheduledLightEvent* e);

#if 1 //START: setEventSchedule
static void setEventSchedule(ScheduledLightEvent* event,
        int id, Day day, long int minute, int control, int randomize)
{
        event->id = id;
        event->day = day;
        event->minute = minute;
        event->event = control;
        event->randomize = randomize;
        resetRandomize(event);
}
#endif //END: setEventSchedule

//START: isInUse
static BOOL isInUse(ScheduledLightEvent * event)
{
    return event->id != UNUSED;
}
//END: isInUse

#if 1 //START: findUnusedEvent2
static ScheduledLightEvent* findUnusedEvent()
{
    int i;
    ScheduledLightEvent* event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (!isInUse(event))
            return event;
    }
    return NULL;
}
#endif //END: findUnusedEvent2

#if 0 //START: findUnusedEvent1
static ScheduledLightEvent* findUnusedEvent(int id)
{
    int i;
    ScheduledLightEvent* event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            event = &eventList[i];
            return event;
        }
    }
    return NULL;
}
#endif //END: findUnusedEvent1

#if 1 //START: scheduleEvent5
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{

    ScheduledLightEvent* event = findUnusedEvent(UNUSED);

    if (event)
        setEventSchedule(event, id, day, minute, control, randomize);
}
#endif //END: scheduleEvent5

#if 0 //START: scheduleEvent4
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{

    ScheduledLightEvent* event = findUnusedEvent(UNUSED);

    if (event)
    {
         event->id = id;
         event->day = day;
         event->minute = minute;
         event->event = control;
         event->randomize = randomize;
         resetRandomize(event);

    }
}
#endif //END: scheduleEvent4


void LightScheduler_ScheduleTurnOn(int id, Day day, long int minute)
{
    scheduleEvent(id, day, minute, TURNON, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOff(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNOFF, RANDOM_OFF);
}

static BOOL matchEvent(ScheduledLightEvent* e, int id, Day day, long int minute)
{
    return e->id == id && e->day == day && e->minute == minute;
}

void LightScheduler_Randomize(int id, Day day, long int minute)
{
    int i;
    ScheduledLightEvent* event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (matchEvent(event, id, day, minute))
        {
            event->randomize = RANDOM_ON;
            resetRandomize(event);
        }
    }
}

void LightScheduler_ScheduleRemove(int id, Day day, long int minute)
{
    int i;
    ScheduledLightEvent* event = eventList;

    for (i = 0; i < MAX_EVENTS; i++, event++)
    {
        if (matchEvent(event, id, day, minute))
            event->id = UNUSED;
    }
}

//START: operateLight
static void operateLight(ScheduledLightEvent * event)
{
    if (TURNON == event->event)
        LightController_TurnOn(event->id);
    else if (TURNOFF == event->event)
        LightController_TurnOff(event->id);
}
//END: operateLight

//START: resetRandomize
static void resetRandomize(ScheduledLightEvent * event)
{
    if (event->randomize == RANDOM_ON)
        event->randomMinutes = RandomMinute_Get();
    else
        event->randomMinutes = 0;
}
//END: resetRandomize

#if 0 //START: scheduleEvent3
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{
    int i;
    ScheduledLightEvent* event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
       {
            event = &eventList[i];
            break;
        }
    }

    if (event)
    {
        event->id = id;
        event->day = day;
        event->minute = minute;
        event->event = control;
        event->randomize = randomize;
        resetRandomize(event);
    }
}
#endif //END: scheduleEvent3

#if 0 //START: scheduleEvent2
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{
    int i;
    ScheduledLightEvent* event = 0;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            event = &eventList[i];
            event->id = id;
            event->day = day;
            event->minute = minute;
            event->event = control;
            event->randomize = randomize;
            resetRandomize(event);
            break;
        }
    }
}
#endif //END: scheduleEvent2

#if 0 //START: scheduleEvent1
static void scheduleEvent(int id, Day day, long int minute, int control,
        int randomize)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (!isInUse(&eventList[i]))
        {
            eventList[i].id = id;
            eventList[i].day = day;
            eventList[i].minute = minute;
            eventList[i].event = control;
            eventList[i].randomize = randomize;
            resetRandomize(&eventList[i]);
            break;
        }
    }
}
#endif //END: scheduleEvent1

#if 0 //START: Time_MatchesMinuteOfDay
BOOL Time_MatchesMinuteOfDay(Time* time, int minute)
{
     return time->minuteOfDay == minute;
}
#endif //END: Time_MatchesMinuteOfDay

#if 0 //START: Time_MatchesDayOfWeek
BOOL Time_MatchesDayOfWeek(Time* time, Day day)
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
#endif //END: Time_MatchesDayOfWeek

#if 0 //START: daysMatch3
static BOOL daysMatch(Day today, Day scheduledDay)
{
    if (scheduledDay == EVERYDAY)
        return TRUE;
    if (scheduledDay == today)
        return TRUE;
    if (scheduledDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (scheduledDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return TRUE;
    return FALSE;
}
#endif //END: daysMatch3

#if 0 //START: daysMatch2
static BOOL daysMatch(Day scheduledDay, Day today)
{
    if (scheduledDay == EVERYDAY)
        return TRUE;
    if (scheduledDay == today)
        return TRUE;
    if (scheduledDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (scheduledDay == WEEKDAY && (today >= MONDAY && today <= FRIDAY))
        return TRUE;
    return FALSE;
}
#endif //END: daysMatch2

#if 0 //START: daysMatch1
static BOOL daysMatch(Day scheduledDay, Day today)
{
    if ((day == EVERYDAY) || (day == today)
             || (day == WEEKEND &&
             (SATURDAY == today || SUNDAY == today))
             || (day == WEEKDAY && (today >= MONDAY
             && today <= FRIDAY)))
        return TRUE;
    return FALSE;
}
#endif //END: daysMatch1

#if 0 //START: isEventDueNow5
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int minute = time->minuteOfDay;
    Day day = event->day;

    if (minute != event->minute + event->randomMinutes)
        return FALSE;

    if (!Time_MatchesDayOfWeek(time, day))
        return FALSE;

    return TRUE;
}
#endif //END: isEventDueNow5

#if 0 //START: isEventDueNow4
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int minute = time->minuteOfDay;
    Day day = event->day;

    if (minute != event->minute + event->randomMinutes)
        return FALSE;

    if (!daysMatch(time, day))
        return FALSE;

    return TRUE;
}
#endif //END: isEventDueNow4

#if 0 //START: isEventDueNow3
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;
    Day day = event->day;

    if (minute != event->minute + event->randomMinutes)
        return FALSE;

#if 1
    if (daysMatch(today, day))
        return TRUE;
#else
    if ( (day == EVERYDAY) || (day == today)
             || (day == WEEKEND &&
             (SATURDAY == today || SUNDAY == today))
             || (day == WEEKDAY && (today >= MONDAY
             && today <= FRIDAY)))
        return TRUE;
#endif
    return FALSE;
}
#endif //END: isEventDueNow3

#if 0 //START: isEventDueNow2
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;
    Day day = event->day;

    if (minute != event->minute + event->randomMinutes)
        return FALSE;

    if ( (day == EVERYDAY) || (day == today)
            || (day == WEEKEND &&
            (SATURDAY == today || SUNDAY == today))
            || (day == WEEKDAY && (today >= MONDAY
            && today <= FRIDAY)))
        return TRUE;

    return FALSE;
}
#endif //END: isEventDueNow2

#if 0 //START: isEventDueNow1
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;
    Day day = event->day;
    if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                (SATURDAY == today || SUNDAY == today)) ||
        (day == WEEKDAY && (today >= MONDAY
                        && today <= FRIDAY)))
    {
        if (minute == event->minute + event->randomMinutes)
            return TRUE;
    }
    return FALSE;
}
#endif //END: isEventDueNow1

#if 1 //START: isEventDueNow6
static BOOL isEventDueNow(Time * time, ScheduledLightEvent * event)
{
    int todaysMinute = event->minute + event->randomMinutes;
    Day day = event->day;

    if (!Time_MatchesMinuteOfDay(time, todaysMinute))
        return FALSE;

    if (!Time_MatchesDayOfWeek(time, day))
        return FALSE;

    return TRUE;
}
#endif //END: isEventDueNow6

#if 1 //START: processEventsDueNow4
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (isInUse(event))
    {
        if (isEventDueNow(time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif  //END: processEventsDueNow4

#if 1 //START: LightScheduler_WakeUp2
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
#endif //END: LightScheduler_WakeUp2


#if 0 //START: processEventsDueNow3
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    if (event->id != UNUSED)
    {
        if (isEventDueNow(time, event))
        {
            operateLight(event);
            resetRandomize(event);
        }
    }
}
#endif  //END: processEventsDueNow3

#if 0 //START: processEventsDueNow2
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        //if (isEventDueNow())
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                        (SATURDAY == today || SUNDAY == today)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            if (minute == event->minute + event->randomMinutes)
            {
                operateLight(event);

                //resetRandomize()
                if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                else
                    event->randomMinutes = 0;
            }
        }
    }
}
#endif  //END: processEventsDueNow2

#if 0
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        //if (isEventDueNow())
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                        (SATURDAY == today || SUNDAY == today)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
            if (minute == event->minute + event->randomMinutes)
            {
                //START: processEventsDueNow1IWish2
                //operateLight(event);
                if (TURNON == event->event)
                    LightController_TurnOn(event->id);
                else if (TURNOFF == event->event)
                    LightController_TurnOff(event->id);
                //END: processEventsDueNow1IWish2

                //resetRandomize()
                if (event->randomize == RANDOM_ON)
                    event->randomMinutes = RandomMinute_Get();
                else
                    event->randomMinutes = 0;
            }
        }
    }
}
#endif



#if 0 //START: processEventsDueNow1IWish
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;

    if (event->id != UNUSED)
    {
        Day day = event->day;
        //if (isEventDueNow())
        if ( (day == EVERYDAY) || (day == today) || (day == WEEKEND &&
                        (SATURDAY == today || SUNDAY == today)) ||
                (day == WEEKDAY && (today >= MONDAY
                                && today <= FRIDAY)))
        {
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
#endif //END: processEventsDueNow1IWish

#if 0 //START: processEventsDueNow1
static void processEventsDueNow(Time * time, ScheduledLightEvent * event)
{
    Day today = time->dayOfWeek;
    int minute = time->minuteOfDay;

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
#endif //END: processEventsDueNow1

#if 0 //START: LightScheduler_WakeUp1
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
#endif //END: LightScheduler_WakeUp1

