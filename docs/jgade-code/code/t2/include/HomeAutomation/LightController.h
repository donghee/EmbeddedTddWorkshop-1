//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#ifndef D_LightController_H
#define D_LightController_H

///////////////////////////////////////////////////////////////////////////////
//
//  LightController is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "LightDriver.h"
#include "common.h"

enum {MAX_LIGHTS = 32};

void LightController_Create(LightDriverType);
void LightController_Destroy();
void LightController_TurnOn(int id);
void LightController_TurnOff(int id);
BOOL LightController_Add(int id, LightDriver*);

void LightController_OverrideInterface(
		LightDriverFunction* Destroy,
		LightDriverFunction* TurnOn,
		LightDriverFunction* TurnOff);

#endif  // D_LightController_H
