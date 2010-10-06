//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.
#include "FakeRandomMinute.h"
#include "CppUTest/TestHarness_c.h"

static int seed = -1;
static int increment = -1;

void FakeRandomMinute_Reset()
{
	seed = -1;
	increment = -1;
}

void FakeRandomMinute_SetSeedAndIncrement(int s, int i)
{
	seed = s;
	increment = i;
}

int FakeRandomMinute_Get()
{
	int result = seed;
	seed += increment;
	return result;
}
