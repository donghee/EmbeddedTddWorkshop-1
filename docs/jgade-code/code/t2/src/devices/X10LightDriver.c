//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#include "X10LightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

//static local variables
struct X10LightDriver
{
    LightDriver base;
    X10_HouseCode house;
    int unit;
};

X10LightDriver* X10LightDriver_Create(int id, X10_HouseCode house, int unit)
{
     X10LightDriver* self = malloc(sizeof(X10LightDriver));
     memset(self, 0, sizeof(X10LightDriver));
     self->base.type = X10;
     self->base.id = id;
     self->house = house;
     self->unit = unit;
     return self;
}

void X10LightDriver_Destroy(LightDriver* super)
{
    X10LightDriver* self = (X10LightDriver*)super;
    free(self);
}

void X10LightDriver_TurnOn(LightDriver* super)
{
//    X10LightDriver* self = (X10LightDriver*)super;
    explodesInTestEnvironment();
}

void X10LightDriver_TurnOff(LightDriver* super)
{
//    X10LightDriver* self = (X10LightDriver*)super;
    explodesInTestEnvironment();
}

