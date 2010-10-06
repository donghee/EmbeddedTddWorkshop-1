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
//END: RememberAllLightStates

int FakeLightController_getLastId(void);
int FakeLightController_getLastState(void);
int FakeLightController_getEventCounts(void);

#endif  // D_FakeLightController_H

#if 0
//START:initial
#ifndef D_FakeLightController_H
#define D_FakeLightController_H

#include "LightController.h"

int FakeLightController_getLastId(void);
int FakeLightController_getLastState(void);

#endif  // D_FakeLightController_H
//END:initial
#endif
