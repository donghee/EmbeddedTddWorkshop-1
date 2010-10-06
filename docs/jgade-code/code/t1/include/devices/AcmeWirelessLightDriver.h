//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_AcmeWirelessLightDriver_H
#define D_AcmeWirelessLightDriver_H

///////////////////////////////////////////////////////////////////////////////
//
//  AcmeWirelessLightDriver is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "LightDriver.h"

typedef struct AcmeWirelessLightDriver AcmeWirelessLightDriver;

typedef enum AcmeWireless_HouseCode { Acme_A,Acme_B,Acme_C,Acme_D,Acme_E,Acme_F,Acme_G } AcmeWireless_HouseCode;

AcmeWirelessLightDriver* AcmeWirelessLightDriver_Create(int lightId, AcmeWireless_HouseCode code, int unitNumber);
void AcmeWirelessLightDriver_Destroy(LightDriver*);
void AcmeWirelessLightDriver_TurnOn(LightDriver*);
void AcmeWirelessLightDriver_TurnOff(LightDriver*);

#endif  // D_AcmeWirelessLightDriver_H
