//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"
#include "string.h"

extern "C"
{
#include "RandomMinute.h"
#include <stdio.h>
}

enum { BOUND=30 };

TEST_GROUP(RandomMinute)
{

    void setup()
    {
        RandomMinute_Create(BOUND);
    }

    void teardown()
    {
    }
}
;

TEST(RandomMinute, GetIsInRange)
{
    int minute;

    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
        if (minute < -BOUND || minute > BOUND)
        {
            printf("bad minute value: %d\n", minute);
            FAIL("Minute out of range");
        }
    }
}

TEST(RandomMinute, AllValuesPossible)
{
    int minute;
    int hit[2*BOUND + 1];
    memset(hit, 0, sizeof(hit));

    for (int i = 0; i < 500; i++)
    {
        minute = RandomMinute_Get();
        if (minute < -BOUND || minute > BOUND)
        {
            printf("bad minute value: %d\n", minute);
            FAIL("Minute out of range");
        }
        hit[minute + BOUND]++;
    }

    for (int i = 0; i < BOUND + 1; i++) {
        CHECK(hit[i] > 0);
    }
}
