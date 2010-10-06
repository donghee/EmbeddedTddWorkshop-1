//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_MockRandomMinute_H
#define D_MockRandomMinute_H

///////////////////////////////////////////////////////////////////////////////
//
//  RandomMinute is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "RandomMinute.h"

void FakeRandomMinute_SetSeedAndIncrement(int seed, int increment);
int FakeRandomMinute_Get();
void FakeRandomMinute_Reset();
#endif  // D_RandomMinute_H
