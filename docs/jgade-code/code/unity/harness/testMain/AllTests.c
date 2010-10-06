#include "unity_fixture.h"

static void runAllTests()
{
    RUN_TEST_GROUP(UnityFixture);
    RUN_TEST_GROUP(UnityOutput);
    RUN_TEST_GROUP(UnityCommandOptions);
    RUN_TEST_GROUP(LeakDetection)
}

int main(int ac, const char* av[])
{
    return UnityMain(ac, av, runAllTests);
}

