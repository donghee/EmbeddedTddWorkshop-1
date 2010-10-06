//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

///////////////////////////////////////////////////////////////////////////////
//
//  FakeTimeService.h
//
//  FakeTimeService is responsible for providing a test stub for TimeService
//
///////////////////////////////////////////////////////////////////////////////
#include "TimeService.h"

void FakeTimeService_SetMinute(long int);
void FakeTimeService_SetDay(int);


#endif  // D_FakeTimeService_H
