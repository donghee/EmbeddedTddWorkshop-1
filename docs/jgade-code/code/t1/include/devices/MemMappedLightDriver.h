//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_MemMappedLightDriver_H
#define D_MemMappedLightDriver_H

///////////////////////////////////////////////////////////////////////////////
//
//  MemMappedLightDriver is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "LightDriver.h"
#include <stdint.h>

typedef struct MemMappedLightDriver MemMappedLightDriver;

MemMappedLightDriver* MemMappedLightDriver_Create(int lightId, uint32_t* address);
void MemMappedLightDriver_Destroy(LightDriver*);
void MemMappedLightDriver_TurnOn(LightDriver*);
void MemMappedLightDriver_TurnOff(LightDriver*);

#endif  // D_MemMappedLightDriver_H
