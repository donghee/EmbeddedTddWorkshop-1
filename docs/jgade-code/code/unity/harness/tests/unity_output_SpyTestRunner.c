
#include "unity_fixture.h"

TEST_GROUP_RUNNER(UnityOutput)
{
    RUN_TEST_CASE(UnityOutput, UnityOutputCharSpy);
    RUN_TEST_CASE(UnityOutput, UnityOutputCharSpyFullBuffer);
}
