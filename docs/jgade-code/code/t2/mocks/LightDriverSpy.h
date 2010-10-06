//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightDriverSpy_H
#define D_LightDriverSpy_H

///////////////////////////////////////////////////////////////////////////////
//
//  LightDriverSpy is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "LightDriver.h"
#include "LightController.h"

enum { NO_LIGHT_ID = -1, LIGHT_STATE_UNKNOWN = -1, LIGHT_OFF = 0, LIGHT_ON = 1 };

typedef struct LightDriverSpy LightDriverSpy;

LightDriverSpy* LightDriverSpy_Create(int id);
void LightDriverSpy_Destroy(LightDriver*);
void LightDriverSpy_TurnOn(LightDriver*);
void LightDriverSpy_TurnOff(LightDriver*);

void LightDriverSpy_Reset();
void LightDriverSpy_AddSpiesToController();
int LightDriverSpy_GetState(int id);
int LightDriverSpy_GetLastId();
int LightDriverSpy_GetLastState();


#endif  // D_LightDriverSpy_H
