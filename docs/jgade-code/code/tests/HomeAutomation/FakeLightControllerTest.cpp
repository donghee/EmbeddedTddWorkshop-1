//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


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
    LightController_On(10);
    LONGS_EQUAL(10, FakeLightController_getLastId());
    LONGS_EQUAL(1, FakeLightController_getLastState());
}
//END: original

//START: RememberAllLightStates
TEST(LightController, RememberAllLightStates)
{
    LONGS_EQUAL(UNKNOWN_STATE, FakeLightController_getLightState(4));

    LightController_On(4);
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLightState(4));

    LightController_Off(4);
    LONGS_EQUAL(LIGHT_OFF, FakeLightController_getLightState(4));
}
//END: RememberAllLightStates
