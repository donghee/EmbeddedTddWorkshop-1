//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
    #include "common.h"
    #include "LightDriver.h"
    #include <stdlib.h>
    #include "CppUTest/TestHarness_c.h"
}

//START: stubs
static int destroyCalled;
static int onCalled;
static int offCalled;
static void destroy(LightDriver* d) { destroyCalled = TRUE; free(d);}
static void on(LightDriver* d) { onCalled = TRUE;}
static void off(LightDriver* d) { offCalled = TRUE;}
//END: stubs

//START: ExampleDriver
typedef struct ExampleDriver
{
    LightDriver base;
    int exampleSpecificData;
} ExampleDriver;
//END: ExampleDriver

//START: ExampleDriver_Create
static ExampleDriver * savedExampleDriver = 0;

LightDriver * ExampleDriver_Create(int id, int exampleSpecificData)
{
    ExampleDriver * exampleDriver = (ExampleDriver*)malloc(sizeof(ExampleDriver));
    savedExampleDriver = exampleDriver;
    exampleDriver->exampleSpecificData = exampleSpecificData;
    return LightDriver_Create(&exampleDriver->base, "Example", id,
            destroy, on, off);
}
//END: ExampleDriver_Create

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

//START: testGroup
TEST_GROUP(LightDriver)
{
    LightDriver * driver;
    int id;

    void setup()
    {
        id = 12;
        savedExampleDriver = 0;
        driver = ExampleDriver_Create(id, 42);

        destroyCalled = FALSE;
        onCalled = FALSE;
        offCalled = FALSE;
    }

    void teardown()
    {
       LightDriver_Destroy(driver);
       CHECK(TRUE == destroyCalled);
    }
};
//END: testGroup

//START: ContainedLightDriverMustBeFirst
TEST(LightDriver, ContainedLightDriverMustBeFirst)
{
    POINTERS_EQUAL(savedExampleDriver, driver);
}
//END: ContainedLightDriverMustBeFirst

//START: DriversHaveTypeAndId
TEST(LightDriver, DriversHaveTypeAndId)
{
    STRCMP_EQUAL("Example", LightDriver_GetType(driver));
    LONGS_EQUAL(id, LightDriver_GetId(driver));
}
//END: DriversHaveTypeAndId

//START: on
TEST(LightDriver, TrunOnDispatchesThroughFunctionPointer)
{
    LightDriver_TurnOn(driver);
    CHECK(FALSE == destroyCalled);
    CHECK(TRUE == onCalled);
    CHECK(FALSE == offCalled);
}
//END: on

//START: off
TEST(LightDriver, TrunOffDispatchesThroughFunctionPointer)
{
    LightDriver_TurnOff(driver);
    CHECK(FALSE == destroyCalled);
    CHECK(FALSE == onCalled);
    CHECK(TRUE == offCalled);
}
//END: off

//START: nullTest
TEST(LightDriver, NullDriverDoesNoHarm)
{
    LightDriver* nullDriver = LightDriver_CreateNull(1);
    STRCMP_EQUAL("NullLightDriver", nullDriver->type);
    LightDriver_TurnOn(nullDriver);
    LightDriver_TurnOff(nullDriver);
    LightDriver_Destroy(nullDriver);
}
//END: nullTest


