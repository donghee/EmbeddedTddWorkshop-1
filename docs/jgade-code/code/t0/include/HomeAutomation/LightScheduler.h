//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightScheduler_H
#define D_LightScheduler_H

//START: Interface
#include "TimeService.h"

enum  { LS_OK=0, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS };

void LightScheduler_Create();
void LightScheduler_Destroy();
int LightScheduler_ScheduleTurnOn(int id, Day day, long int minute);
int LightScheduler_ScheduleTurnOff(int id, Day day, long int minute);
void LightScheduler_Randomize(int id, Day day, long int minute);
void LightScheduler_ScheduleRemove(int id, Day day, long int minute);
void LightScheduler_WakeUp();
//END: Interface
#endif  // D_LightScheduler_H
