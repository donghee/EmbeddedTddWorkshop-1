//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




extern "C"
{
#include "MemMappedLightDriver.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"



TEST_GROUP(MemMappedLightDriver)
{
    MemMappedLightDriver* memMappedLightDriver;
    uint32_t mockLights;

    void setup()
    {
      memMappedLightDriver = MemMappedLightDriver_Create(4, &mockLights);
    }

    void teardown()
    {
       MemMappedLightDriver_Destroy( (LightDriver*)memMappedLightDriver);
    }
};

TEST(MemMappedLightDriver, Create)
{
     LightDriver* driver =  (LightDriver*)memMappedLightDriver;
     LONGS_EQUAL(MemoryMapped, driver->type);
     LONGS_EQUAL(4, driver->id);
}

