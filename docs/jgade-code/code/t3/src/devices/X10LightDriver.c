//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "X10LightDriver.h"
#include "LightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

void X10LightDriver_Destroy(LightDriver*);
void X10LightDriver_TurnOn(LightDriver*);
void X10LightDriver_TurnOff(LightDriver*);

//START: struct
typedef struct X10LightDriver
{
    LightDriver base;
    X10_HouseCode house;
    int unit;
    //Other X10 data needed
}X10LightDriver;
//END: struct

//START: create
LightDriver* X10LightDriver_Create(int id, X10_HouseCode house, int unit)
{
    X10LightDriver* self = malloc(sizeof(X10LightDriver));
    memset(self, 0, sizeof(X10LightDriver));
    self->house = house;
    self->unit = unit;
    return LightDriver_Create(&self->base, "X10", id, X10LightDriver_Destroy,
            X10LightDriver_TurnOn, X10LightDriver_TurnOff);
}
//END: create

//START: destroy
void X10LightDriver_Destroy(LightDriver* base)
{
    //X10 specific resource cleanup and hardware shutdown
    free(base);
}
//END: destroy

//START: on
void X10LightDriver_TurnOn(LightDriver* base)
{
    X10LightDriver* self = (X10LightDriver*) base;
    int house = self->house;
    int unit = self->unit;
    //X10 implementation
    //END: on
    volatile int* justToGetRidOfWarning = (int*) 0xdeadbeef;
    *justToGetRidOfWarning += (house + unit);
    explodesInTestEnvironment(self);
    //START: on
}
//END: on

void X10LightDriver_TurnOff(LightDriver* base)
{
    X10LightDriver* self = (X10LightDriver*) base;
    int house = self->house;
    int unit = self->unit;
    //X10 implementation
    //END: on
    volatile int* justToGetRidOfWarning = (int*) 0xdeadbeef;
    *justToGetRidOfWarning += (house + unit);
    explodesInTestEnvironment(self);
    //START: on
}

