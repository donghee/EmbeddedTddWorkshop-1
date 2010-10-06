//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "X10LightDriver.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(X10LightDriver)
{
    X10LightDriver* x10LightDriver;

    void setup()
    {
      x10LightDriver = X10LightDriver_Create(1, X10_A, 12);
    }

    void teardown()
    {
       X10LightDriver_Destroy((LightDriver*)x10LightDriver);
    }
};

TEST(X10LightDriver, Create)
{
    LightDriver* driver =  (LightDriver*)x10LightDriver;
    LONGS_EQUAL(X10, driver->type);
    LONGS_EQUAL(1, driver->id);
}

