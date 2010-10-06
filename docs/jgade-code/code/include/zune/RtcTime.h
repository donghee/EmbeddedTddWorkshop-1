#ifndef D_RtcTime_H
#define D_RtcTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  RtcTime is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "common.h"

typedef struct RtcTime RtcTime;

RtcTime* RtcTime_Create(int daysSince1980);
void RtcTime_Destroy(RtcTime*);
int RtcTime_GetYear(RtcTime*);
int RtcTime_GetMonth(RtcTime*);
int RtcTime_GetDayOfMonth(RtcTime*);
int RtcTime_GetDayOfWeek(RtcTime*);
BOOL isLeapYear(int year);

enum {
    Sunday = 0, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
};


#endif  // D_RtcTime_H
