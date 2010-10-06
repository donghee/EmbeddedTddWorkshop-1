//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LedDriver_H
#define D_LedDriver_H
//START: uint16_t
#include <stdint.h>
//END: uint16_t

#define TRUE 1
#define FALSE 0
typedef int BOOL;


//START: final
void LedDriver_Create(uint16_t * ledsAddress);
void LedDriver_Destroy();

//START: TurnOn
void LedDriver_TurnOn(int ledNumber);
//END: TurnOn
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn();
void LedDriver_TurnAllOff();
//START: IsOn
BOOL LedDriver_IsOn(int ledNumber);
//END: IsOn
BOOL LedDriver_IsOff(int ledNumber);
//END: final
#endif  // D_LedDriver_H

/*
 * Intermediate examples below this comment
 */

#if 0 //START: StartingPoint
#ifndef D_LedDriver_H
#define D_LedDriver_H

void LedDriver_Create(void);
void LedDriver_Destroy(void);

#endif  // D_LedDriver_H
//END: StartingPoint

#if 0 //START: FirstThreeTests
#ifndef D_LedDriver_H
#define D_LedDriver_H

void LedDriver_Create(void);
void LedDriver_Destroy(void);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
//END: FirstThreeTests
#endif


#endif  // D_LedDriver_H


#endif
