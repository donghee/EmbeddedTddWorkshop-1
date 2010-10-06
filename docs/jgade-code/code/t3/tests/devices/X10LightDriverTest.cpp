//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


//START:testGroup
extern "C"
{
#include "X10LightDriver.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(X10LightDriver)
{
    LightDriver* lightDriver;

    void setup()
    {
      lightDriver = X10LightDriver_Create(1, X10_A, 12);
    }

    void teardown()
    {
       LightDriver_Destroy(lightDriver);
    }
};

TEST(X10LightDriver, Create)
{
     STRCMP_EQUAL("X10", lightDriver->type);
     LONGS_EQUAL(1, lightDriver->id);
}
//END: testGroup

