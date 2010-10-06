//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net

#if 1
//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightScheduler_H
#define D_LightScheduler_H

//START: Interface
void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_ScheduleTurnOn(int id, int day, long int minute);
void LightScheduler_Randomize(int id, int day, long int minute);
void LightScheduler_ScheduleTurnOff(int id, int day, long int minute);
void LightScheduler_ScheduleRemove(int id, int day, long int minute);
void LightScheduler_WakeUp();
//END: Interface
#endif  // D_LightScheduler_H

#else

//START: Interface2
#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#include "TimeService.h"

enum Day {
    NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minute);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minute);
void LightScheduler_ScheduleRemove(int id, Day day, int minute);
void LightScheduler_Wakeup(Time*);

#endif  // D_LightScheduler_H
//END: Interface2

#if 0
//START: Interface
#ifndef D_LightScheduler_H
#define D_LightScheduler_H


enum Day {
    NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minute);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minute);
void LightScheduler_ScheduleRemove(int id, Day day, int minute);
void LightScheduler_Wakeup(void);

#endif  // D_LightScheduler_H
//END: Interface
#endif
