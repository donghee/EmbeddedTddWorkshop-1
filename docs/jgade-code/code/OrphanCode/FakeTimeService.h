#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum {TIME_UNKNOWN = -1};

void FakeTimeService_SetMinute(int);
void FakeTimeService_SetDay(int);
WakeupCallback FakeTimeSource_GetAlarmCallback();
int FakeTimeSource_GetAlarmPeriod();
void FakeTimeService_MinuteIsUp();

#endif  // D_FakeTimeService_H
