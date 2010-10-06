//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_TimeService_H
#define D_TimeService_H

///////////////////////////////////////////////////////////////////////////////
//
//  TimeService is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

#include "common.h"
enum DAY {
    EVERYDAY=-3, WEEKDAY=-2, WEEKEND=-1,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

void TimeService_Create(void);
void TimeService_Destroy(void);
int TimeService_GetMinute(void);
int TimeService_GetDay(void);

BOOL TimeService_MatchesNow(int reactionDay, int minute);

#endif  // D_TimeService_H
