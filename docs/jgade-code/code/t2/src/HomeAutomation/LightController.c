//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "LightController.h"
#include <stdlib.h>
#include <memory.h>
#include "X10LightDriver.h"
#include "LightDriverSpy.h"
#include "AcmeWirelessLightDriver.h"
#include "MemMappedLightDriver.h"
#include "RuntimeError.h"
#include "common.h"


//START: hidden_data
static void nullDriver(LightDriver * d) {}
static LightDriver * lightDrivers[MAX_LIGHTS] = {NULL};
static LightDriverFunction * lightDriver_TurnOn = nullDriver;
static LightDriverFunction * lightDriver_TurnOff = nullDriver;
static LightDriverFunction * lightDriver_Destroy = nullDriver;
//END: hidden_data

//START: fp_init
static void setDriverFunctions(LightDriverType lightType)
{
    switch(lightType)
    {
    case X10:
        LightController_OverrideInterface(X10LightDriver_Destroy,
                X10LightDriver_TurnOn, X10LightDriver_TurnOff);
        break;
    case AcmeWireless:
        LightController_OverrideInterface(AcmeWirelessLightDriver_Destroy,
                AcmeWirelessLightDriver_TurnOn, AcmeWirelessLightDriver_TurnOff);
        break;
    case MemoryMapped:
        LightController_OverrideInterface(MemMappedLightDriver_Destroy,
                MemMappedLightDriver_TurnOn, MemMappedLightDriver_TurnOff);
        break;
    case Unknown:
    default:
        RUNTIME_ERROR("Unknown light driver type %d", lightType);
        break;
    }
}
//END: fp_init

//START: create
void LightController_Create(LightDriverType type)
{
    memset(lightDrivers, 0, sizeof(lightDrivers));
    setDriverFunctions(type);
}
//END: create

//START: destroy
void LightController_Destroy(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver * driver = lightDrivers[i];
        if (driver != NULL)
            lightDriver_Destroy(driver);
        lightDrivers[i] = NULL;
    }
}
//END: destroy

//START: add
BOOL LightController_Add(int id, LightDriver * lightDriver)
{
    if (id < 0 || id >= MAX_LIGHTS)
        return FALSE;

    if (lightDrivers[id] != NULL)
        lightDriver_Destroy(lightDrivers[id]);

    lightDrivers[id] = lightDriver;
    return TRUE;
}
//END: add

//START: override
void LightController_OverrideInterface(
        LightDriverFunction * destroy,
        LightDriverFunction * turnOn,
        LightDriverFunction * turnOff)
{
    lightDriver_TurnOn = turnOn;
    lightDriver_TurnOff = turnOff;
    lightDriver_Destroy = destroy;
}
//END: override

//START: on_off
void LightController_TurnOn(int id)
{
    if (lightDrivers[id])
        lightDriver_TurnOn(lightDrivers[id]);
}

void LightController_TurnOff(int id)
{
    if (lightDrivers[id])
        lightDriver_TurnOff(lightDrivers[id]);
}
//END: on_off






