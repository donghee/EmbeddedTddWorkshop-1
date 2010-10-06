//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightScheduler_H
#define D_LightScheduler_H

//START: interface
void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_ScheduleTurnOn(int id, int day, long int minute);
void LightScheduler_Randomize(int id, int day, long int minute);
void LightScheduler_ScheduleTurnOff(int id, int day, long int minute);
void LightScheduler_ScheduleRemove(int id, int day, long int minute);
void LightScheduler_WakeUp();
//END: interface
#endif  // D_LightScheduler_H