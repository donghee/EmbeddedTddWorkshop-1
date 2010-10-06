//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "LightScheduler.h"
#include "FakeLightController.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}
#include "CppUTest/TestHarness.h"

#if 1//START: UT_PTR_SET
TEST_GROUP(LightSchedulerRamdomize)
{
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
        UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
    }
};
#endif //END: UT_PTR_SET

//START: EnableRandomize
TEST(LightSchedulerRamdomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);

    FakeTimeService_SetMinute(600-10);

    LightScheduler_WakeUp();

    LONGS_EQUAL(4, FakeLightController_getLastId());
    LONGS_EQUAL(LIGHT_ON, FakeLightController_getLastState());
}
//END: EnableRandomize

#if 0 //START: manualPtrInitRestore
TEST_GROUP(LightSchedulerRamdomize)
{
    int (*savedRandomMinute_Get)();

    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
        savedRandomMinute_Get = RandomMinute_Get;
        RandomMinute_Get = FakeRandomMinute_Get;
    }

    void teardown()
    {
        LightScheduler_Destroy();
        LightController_Destroy();
        RandomMinute_Get = savedRandomMinute_Get;
    }
};
#endif //END: manualPtrInitRestore

#if 0
TEST(LightSchedulerRamdomize, EnableRandomizeEarlyOnlyOneEventFires)
{
    UT_PTR_SET(RandomMinute_Get, FakeRandomMinute_Get);
    FakeRandomMinute_SetFirstAndIncrement(-10, 1);

    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);

    FakeTimeService_SetMinute(590);
    LightScheduler_WakeUp();
    LightController_Create();
    FakeTimeService_SetMinute(591);
    LightScheduler_WakeUp();

    LONGS_EQUAL(NO_ID, FakeLightController_getLastId());
}
#endif
