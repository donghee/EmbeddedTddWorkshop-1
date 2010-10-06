extern "C"
{
#include "LedDriver.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LedDriver)
{
    void setup()
    {
      LedDriver_Create();
    }

    void teardown()
    {
       LedDriver_Destroy();
    }
};

TEST(LedDriver, Create)
{
//  FAIL("Start here");
}

