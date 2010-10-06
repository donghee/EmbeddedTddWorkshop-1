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

enum {
    TURNON, TURNOFF, DIM, RANDOM_ON, RANDOM_OFF
};

enum {
    MAX_EVENTS = 64,
    UNUSED = -1
};

typedef struct {
    int id;
    int day;
    long int minute;
    int event;
    int randomize;
    int randomMinutes;
    int extraRandomEventPreventer;

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

static void ScheduledLightEvent_Randomize(ScheduledLightEvent* e)
{
    if (e->randomize == RANDOM_ON)
        e->randomMinutes = RandomMinute_Get();
    else
        e->randomMinutes = 0;
}
static void scheduleEvent(int id, int day, long int minute, int event, int randomize)
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
            eventList[i].extraRandomEventPreventer = 0;
            ScheduledLightEvent_Randomize(&eventList[i]);
            break;
        }
    }
}

void LightScheduler_ScheduleTurnOn(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNON, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOnRandomize(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNON, RANDOM_ON);
}

void LightScheduler_ScheduleTurnOff(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNOFF, RANDOM_OFF);
}

void LightScheduler_ScheduleTurnOffRandomize(int id, int day, long int minute)
{
    scheduleEvent(id, day, minute, TURNON, RANDOM_ON);
}

static BOOL randomEventAlreadyHappenedToday(ScheduledLightEvent* lightEvent)
{
	if (lightEvent->extraRandomEventPreventer > 0)
	{
		lightEvent->extraRandomEventPreventer--;
		return TRUE;
	}
	return FALSE;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
    if (TURNON == lightEvent->event)
         LightController_TurnOn(lightEvent->id);
    else if (TURNOFF == lightEvent->event)
         LightController_TurnOff(lightEvent->id);
}

static void preventAnotherRandomLightOperation(ScheduledLightEvent* lightEvent)
{
	if (lightEvent->randomize == RANDOM_ON)
		lightEvent->extraRandomEventPreventer = 61;
}

static void checkEvent(ScheduledLightEvent* lightEvent)
{
    if (randomEventAlreadyHappenedToday(lightEvent))
        return;

    if (!TimeService_MatchesNow(lightEvent->day, lightEvent->minute + lightEvent->randomMinutes))
        return;

    operateLight(lightEvent);

    ScheduledLightEvent_Randomize(lightEvent);
    preventAnotherRandomLightOperation(lightEvent);
}

void LightScheduler_TimeToCheckTheSchedule(void)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id != UNUSED)
            checkEvent(&eventList[i]);
    }
}

void LightScheduler_ScheduleRemove(int id, int day, long int minute)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (eventList[i].id == id
        && eventList[i].day == day
        && eventList[i].minute == minute)
        {
            eventList[i].id = UNUSED;
        }
    }
}
