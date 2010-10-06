//START: original
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeLightController.h"
}

TEST_GROUP(LightController)
{
    void setup()
    {
      LightController_Create();
    }

    void teardown()
    {
       LightController_Destroy();
    }
};

TEST(LightController, Create)
{
    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLastState());
}

TEST(LightController, RememberTheLastLightIdControlled)
{
    LightController_TurnOn(10);
    LONGS_EQUAL(10, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
}
//END: original

//START: RememberAllLightStates
TEST(LightController, RememberAllLightStates)
{
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLightState(4));

    LightController_TurnOn(4);
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLightState(4));

    LightController_TurnOff(4);
    LONGS_EQUAL(LIGHT_OFF, FakeLightController_getLightState(4));
}
//END: RememberAllLightStates
