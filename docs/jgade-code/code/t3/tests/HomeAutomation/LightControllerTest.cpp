//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "LightController.h"
#include "LightDriverSpy.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

//START: tests
TEST_GROUP(LightController)
{
    void setup()
    {
        LightController_Create();
        LightDriverSpy_AddSpiesToController();
    }

    void teardown()
    {
        LightController_Destroy();
    }
};

//END: tests
TEST(LightController, Create)
{
}

TEST(LightController, DriverIsDestroyedByLightController)
{
    LightDriver* spy = LightDriverSpy_Create(1);
    LightController_Add(1, spy);
}

//START: tests
TEST(LightController, TurnOn)
{
    LightController_TurnOn(1);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

TEST(LightController, TurnOff)
{
    LightController_TurnOff(14);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(14));
}
//END: tests

TEST(LightController, AllDriversDestroyed)
{
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver* spy = LightDriverSpy_Create(i);
        LONGS_EQUAL(TRUE, LightController_Add(i, spy));
    }
}


//START: boundary
TEST(LightController, ValidIdLowerRange)
{
    LightDriver* spy = LightDriverSpy_Create(0);
    LONGS_EQUAL(TRUE, LightController_Add(0, spy));
}

TEST(LightController, ValidIdUpperRange)
{
    LightDriver* spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(TRUE, LightController_Add(MAX_LIGHTS-1, spy));
}

TEST(LightController, InValidIdBeyondUpperRange)
{
    LightDriver* spy = LightDriverSpy_Create(MAX_LIGHTS);
    LONGS_EQUAL(FALSE, LightController_Add(MAX_LIGHTS, spy));
    free(spy);
}

TEST(LightController, RejectsNullDrivers)
{
    LONGS_EQUAL(FALSE, LightController_Add(1, NULL));
}
//END: boundary


//START: remove
TEST(LightController, RemoveExistingLightDriverSucceeds)
{
    CHECK(LightController_Remove(10));
}

TEST(LightController, RemoveNonExistingLightDriverDoesNoHarm)
{
    CHECK(LightController_Remove(10));
    CHECK(LightController_Remove(10));
}
//END: remove
