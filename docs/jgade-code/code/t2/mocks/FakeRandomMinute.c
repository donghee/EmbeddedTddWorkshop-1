//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


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

