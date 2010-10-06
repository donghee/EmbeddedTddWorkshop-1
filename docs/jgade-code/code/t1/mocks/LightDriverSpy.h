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

void LightDriverSpy_Reset();
void LightDriverSpy_AddAllToController();
LightDriverSpy* LightDriverSpy_Create(int id);
void LightDriverSpy_Destroy(LightDriver*);
void LightDriverSpy_TurnOn(LightDriver*);
void LightDriverSpy_TurnOff(LightDriver*);
int LightDriverSpy_GetState(int id);
int LightDriverSpy_GetLastId();
int LightDriverSpy_GetLastState();


#endif  // D_LightDriverSpy_H
