//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "MemMappedLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

//static local variables
struct MemMappedLightDriver
{
    LightDriver base;
    uint32_t* address;
    //etc
};

LightDriver* MemMappedLightDriver_Create(int id, uint32_t* address)
{
    MemMappedLightDriver* self = malloc(sizeof(MemMappedLightDriver));
    memset(self, 0, sizeof(MemMappedLightDriver));
    self->address = address;
    return LightDriver_Create(&self->base, "MemoryMapped", id,
            MemMappedLightDriver_Destroy,
            MemMappedLightDriver_TurnOn,
            MemMappedLightDriver_TurnOff);
}

void MemMappedLightDriver_Destroy(LightDriver* super)
{
    free(super);
}

void MemMappedLightDriver_TurnOn(LightDriver* super)
{
    MemMappedLightDriver* self = (MemMappedLightDriver*)super;
    explodesInTestEnvironment(self);
}

void MemMappedLightDriver_TurnOff(LightDriver* super)
{
    MemMappedLightDriver* self = (MemMappedLightDriver*)super;
    explodesInTestEnvironment(self);
}

