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

void LightDriverSpy_AddSpiesToController()
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver* spy = (LightDriver*)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
}

LightDriver* LightDriverSpy_Create(int id)
{
    LightDriver* self = malloc(sizeof(LightDriverSpy));
    return LightDriver_Create(self, "Spy", id,
            LightDriverSpy_Destroy, LightDriverSpy_TurnOn, LightDriverSpy_TurnOff);
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
