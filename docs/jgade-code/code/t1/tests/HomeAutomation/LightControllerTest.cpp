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

TEST_GROUP(LightController)
{
    void setup()
    {
      LightController_Create();
      LightDriverSpy_AddAllToController();
    }

    void teardown()
    {
       LightController_Destroy();
    }
};

TEST(LightController, CreateDestroy)
{
}

TEST(LightController, DriverIsDestroyedByLightController)
{
	LightDriverSpy* spy = LightDriverSpy_Create(1);
	LightController_Add(1, (LightDriver*)spy);
}

TEST(LightController, TurnOn)
{
	LightDriverSpy* spy = LightDriverSpy_Create(1);
	LightController_Add(1, (LightDriver*)spy);
	LightController_TurnOn(1);
	LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

TEST(LightController, TurnOff)
{
	LightDriverSpy* spy = LightDriverSpy_Create(1);
	LightController_Add(1, (LightDriver*)spy);
	LightController_TurnOff(1);
	LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightController, AllDriversDestroyed)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		LightDriverSpy* spy = LightDriverSpy_Create(i);
		LONGS_EQUAL(TRUE, LightController_Add(i, (LightDriver*)spy));
	}
}

TEST(LightController, ValidIdLowerRange)
{
	LightDriverSpy* spy = LightDriverSpy_Create(0);
	LONGS_EQUAL(TRUE, LightController_Add(0, (LightDriver*)spy));
}

TEST(LightController, ValidIdUpperRange)
{
	LightDriverSpy* spy = LightDriverSpy_Create(MAX_LIGHTS);
	LONGS_EQUAL(TRUE, LightController_Add(MAX_LIGHTS-1, (LightDriver*)spy));
}

TEST(LightController, InValidIdBeyondUpperRange)
{
	LightDriverSpy* spy = LightDriverSpy_Create(MAX_LIGHTS);
	LONGS_EQUAL(FALSE, LightController_Add(MAX_LIGHTS, (LightDriver*)spy));
	free(spy);
}

TEST(LightController, NonAddedLightDoesNothing)
{
    LightController_Add(1, (LightDriver*)NULL);
    LightController_TurnOn(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
    LightController_TurnOff(1);
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}



