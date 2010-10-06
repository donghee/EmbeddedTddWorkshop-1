//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

#ifndef D_FakeRandomMinute_H
#define D_FakeRandomMinute_H

///////////////////////////////////////////////////////////////////////////////
//
//  RandomMinute is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "RandomMinute.h"

void FakeRandomMinute_SetFirstAndIncrement(int seed, int increment);
int FakeRandomMinute_Get();
void FackRandomMinute_Reset();
#endif  // D_RandomMinute_H
