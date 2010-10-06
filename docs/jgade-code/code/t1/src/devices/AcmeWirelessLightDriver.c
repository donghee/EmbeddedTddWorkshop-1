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
    int key;
    char* ssid;
    char* wep;
    //etc
};

AcmeWirelessLightDriver* AcmeWirelessLightDriver_Create(int id, AcmeWireless_HouseCode code, int unitNumber)
{
     AcmeWirelessLightDriver* self = malloc(sizeof(AcmeWirelessLightDriver));
     memset(self, 0, sizeof(AcmeWirelessLightDriver));
     self->base.type = AcmeWireless;
     self->base.id = id;
     return self;
}

void AcmeWirelessLightDriver_Destroy(LightDriver* super)
{
    free(super);
}

void AcmeWirelessLightDriver_TurnOn(LightDriver* super)
{
    explodesInTestEnvironment();
}

void AcmeWirelessLightDriver_TurnOff(LightDriver* super)
{
    explodesInTestEnvironment();
}
