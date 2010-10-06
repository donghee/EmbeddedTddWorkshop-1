//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "LightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

//START: create
LightDriver* LightDriver_Create(LightDriver* self,
        const char* type, int id,
        LightDriverFunction* destroy,
        LightDriverFunction* on,
        LightDriverFunction* off)
{
    self->type = type;
    self->id = id;
    self->destroy = destroy;
    self->on = on;
    self->off = off;

     return self;
}

//END: create

//START: destroyOnOff
void LightDriver_Destroy(LightDriver* self)
{
    self->destroy(self);
}

void LightDriver_TurnOn(LightDriver* self)
{
    self->on(self);
}

void LightDriver_TurnOff(LightDriver* self)
{
    self->off(self);
}
//END: destroyOnOff

//START: createNull
static void nullDriver(LightDriver* d) {}
static void nullDestroyer(LightDriver* d) { free(d); }

LightDriver* LightDriver_CreateNull(int id)
{
    LightDriver* self = malloc(sizeof(LightDriver));
    return LightDriver_Create(self, "NullLightDriver", id,
                nullDestroyer, nullDriver, nullDriver);
}
//END: createNull

//START: helpers
const char * LightDriver_GetType(LightDriver* driver)
{
    return driver->type;
}

int LightDriver_GetId(LightDriver* driver)
{
    return driver->id;
}

