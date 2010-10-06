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
#include "common.h"

//START: hidden_data

static LightDriver* lightDrivers[MAX_LIGHTS] = { NULL };

//END: hidden_data

//START: create
void LightController_Create()
{
    memset(lightDrivers, 0, sizeof(lightDrivers));
}
//END: create

//START: destroy
void LightController_Destroy(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver* driver = lightDrivers[i];
        if (driver != NULL)
            LightDriver_Destroy(driver);
        lightDrivers[i] = NULL;
    }
}
//END: destroy

//START: add
BOOL LightController_Add(int id, LightDriver* lightDriver)
{
    if (id < 0 || id >= MAX_LIGHTS || !lightDriver)
        return FALSE;

    if (lightDrivers[id] != NULL)
        LightDriver_Destroy(lightDrivers[id]);

    lightDrivers[id] = lightDriver;
    return TRUE;
}
//END: add

//START: remove
BOOL LightController_Remove(int id)
{
    if (id < 0 || id >= MAX_LIGHTS)
        return FALSE;

    if (lightDrivers[id] != NULL)
        LightDriver_Destroy(lightDrivers[id]);

    lightDrivers[id] = NULL;
    return TRUE;
}
//END: remove

//START: turnOnOff
void LightController_TurnOn(int id)
{
    LightDriver_TurnOn(lightDrivers[id]);
}

void LightController_TurnOff(int id)
{
    LightDriver_TurnOff(lightDrivers[id]);
}
//END: turnOnOff
