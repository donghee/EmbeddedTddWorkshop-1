//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_FakeLightController_H
#define D_FakeLightController_H

#include "LightController.h"

//START: RememberAllLightStates
typedef enum
{
	NO_ID = -1, UNKNOWN_STATE = -1,
	LIGHT_OFF = 0, LIGHT_ON = 1
} LightState;

LightState FakeLightController_getLightState(int id);
int FakeLightController_getLastId();
int FakeLightController_getLastState();

//END: RememberAllLightStates
#endif  // D_FakeLightController_H

#if 0
//START:initial
#ifndef D_FakeLightController_H
#define D_FakeLightController_H

#include "LightController.h"

int FakeLightController_getLastId();
int FakeLightController_getLastState();

#endif  // D_FakeLightController_H
//END:initial
#endif
