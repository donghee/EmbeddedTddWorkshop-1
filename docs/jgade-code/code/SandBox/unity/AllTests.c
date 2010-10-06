//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net

#include "unity_fixture.h"

static void runAllTests()
{
    RUN_TEST_GROUP(LedDriver);
}

int main(int ac, const char* av[])
{
    return UnityMain(ac, av, runAllTests);
}
