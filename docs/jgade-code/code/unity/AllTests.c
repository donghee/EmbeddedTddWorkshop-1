/*
 * all_tests.c
 *
 *  Created on: Apr 15, 2010
 *      Author: james
 */

//START: sprintf
//START: StartingPoint
#include "unity_fixture.h"

//END: StartingPoint
//END: sprintf

#if 0 //START: StartingPoint
static void runAllTests()
{
    RUN_TEST_GROUP(LedDriver);
}
#endif //END: StartingPoint

#if 0 //START: sprintf
static void runAllTests()
{
    RUN_TEST_GROUP(sprintf);
}
#endif //END: sprintf

static void runAllTests()
{
    //    RUN_TEST_GROUP(unity);
    RUN_TEST_GROUP(LedDriver);
    RUN_TEST_GROUP(sprintf);
    RUN_TEST_GROUP(UnityFixture);
    RUN_TEST_GROUP(UnityOutput);
    RUN_TEST_GROUP(UnityCommandOptions);
    RUN_TEST_GROUP(LeakDetection)
}

//START: StartingPoint
//START: sprintf

int main(int ac, const char* av[])
{
    return UnityMain(ac, av, runAllTests);
}
//END: StartingPoint
//END: sprintf
