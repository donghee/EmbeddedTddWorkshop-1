//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "FakeLightController.h"
#include "memory.h"

//local variables

static int lastId;
static int lastLevel;
static int count;
static int lights[MAX_LIGHTS];

void LightController_Create(void)
{
    lastId = NO_ID;
    lastLevel = UNKNOWN_STATE;
    count = 0;
    memset(lights, UNKNOWN_STATE, sizeof(lights));
}

void LightController_Destroy()
{
}

int FakeLightController_getLastId(void)
{
    return lastId;
}

int FakeLightController_getLastState(void)
{
    return lastLevel;
}

static int isIdInRange(int id)
{
    return id > 0 && id <=32;
}
void LightController_On(int id)
{
    lastId = id;
    lastLevel = 1;
    count++;
    if (isIdInRange(id))
        lights[id-1] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastLevel = 0;
    count++;
    if (isIdInRange(id))
        lights[id-1] = LIGHT_OFF;
}

int FakeLightController_getEventCounts(void)
{
    return count;
}

LightState FakeLightController_getLightState(int id)
{
    if (!isIdInRange(id))
        return UNKNOWN_STATE;
    return lights[id-1];
}

#if 0
//START:initial
#include "LightController.h"

//local variables

static int lastId; //<callout id="co.LightController.statics" />
static int lastLevel;

void LightController_Create(void) //<callout id="co.LightController.init" />
{
    lastId = -1;
    lastLevel = -1;
}

void LightController_Destroy()
{
}

void LightController_On(int id) //<callout id="co.LightController.gather1" />
{
    lastId = id;
    lastLevel = 1;
}

void LightController_Off(int id) //<callout id="co.LightController.gather2" />
{
    lastId = id;
    lastLevel = 0;
}

int FakeLightController_getLastId(void) //<callout id="co.LightController.report1" />
{
    return lastId;
}

int FakeLightController_getLastState(void)//<callout id="co.LightController.report2" />
{
    return lastLevel;
}

//END:initial

#endif
