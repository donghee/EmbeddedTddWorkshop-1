//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "AcmeWirelessLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

//static local variables
struct AcmeWirelessLightDriver
{
    LightDriver base;
    int channel;
    AcmeWireless_HouseCode code;
    int unit;
//etc
};

LightDriver* AcmeWirelessLightDriver_Create(int id, int channel,
        AcmeWireless_HouseCode code, int unitNumber)
{
    AcmeWirelessLightDriver* self = malloc(sizeof(AcmeWirelessLightDriver));
    memset(self, 0, sizeof(AcmeWirelessLightDriver));
    self->channel = channel;
    self->code = code;
    self->unit = unitNumber;
    return LightDriver_Create(&self->base, "AcmeWireless", id,
            AcmeWirelessLightDriver_Destroy,
            AcmeWirelessLightDriver_TurnOn,
            AcmeWirelessLightDriver_TurnOff);
}

void AcmeWirelessLightDriver_Destroy(LightDriver* super)
{
    free(super);
}

void AcmeWirelessLightDriver_TurnOn(LightDriver* super)
{
    AcmeWirelessLightDriver* self = (AcmeWirelessLightDriver*)super;
    explodesInTestEnvironment(self);
}

void AcmeWirelessLightDriver_TurnOff(LightDriver* super)
{
    AcmeWirelessLightDriver* self = (AcmeWirelessLightDriver*)super;
    explodesInTestEnvironment(self);
}
