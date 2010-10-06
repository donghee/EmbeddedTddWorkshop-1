//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


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
