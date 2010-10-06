//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "LightDriverSpy.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"
#include "CppUTest/TestHarness_c.h"


struct LightDriverSpy
{
    LightDriver base;
};

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

void LightDriverSpy_Reset()
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        states[i] = LIGHT_STATE_UNKNOWN;
    }
    lastId = NO_LIGHT_ID;
    lastState = LIGHT_STATE_UNKNOWN;
}

//START: AddSpies
void LightDriverSpy_AddSpiesToController()
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver* spy = (LightDriver*)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
    LightController_OverrideInterface(LightDriverSpy_Destroy,
            LightDriverSpy_TurnOn, LightDriverSpy_TurnOff);
}
//END: AddSpies


LightDriverSpy* LightDriverSpy_Create(int id)
{
    LightDriverSpy* self = malloc(sizeof(LightDriverSpy));
    self->base.type = Unknown;
    self->base.id = id;
    return self;
}

void LightDriverSpy_Destroy(LightDriver* super)
{
    LightDriverSpy* self = (LightDriverSpy*)super;
    states[self->base.id] = LIGHT_STATE_UNKNOWN;
    free(self);
}

static void save(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}

void LightDriverSpy_TurnOn(LightDriver* super)
{
    LightDriverSpy* self = (LightDriverSpy*)super;
    save(self->base.id, LIGHT_ON);
}

void LightDriverSpy_TurnOff(LightDriver* super)
{
    LightDriverSpy* self = (LightDriverSpy*)super;
    save(self->base.id, LIGHT_OFF);
}

int LightDriverSpy_GetState(int id)
{
    return states[id];
}

int LightDriverSpy_GetLastId()
{
    return lastId;
}

int LightDriverSpy_GetLastState()
{
    return lastState;
}

