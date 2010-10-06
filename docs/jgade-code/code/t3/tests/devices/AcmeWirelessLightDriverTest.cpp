//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "AcmeWirelessLightDriver.h"
}

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(AcmeWirelessLightDriver)
{
    LightDriver* lightDriver;

    void setup()
    {
      lightDriver = AcmeWirelessLightDriver_Create(1, 42, Acme_G, 16);
    }

    void teardown()
    {
       AcmeWirelessLightDriver_Destroy(lightDriver);
    }
};

TEST(AcmeWirelessLightDriver, Create)
{
     LightDriver* driver = lightDriver;
     STRCMP_EQUAL("AcmeWireless", driver->type);
     LONGS_EQUAL(1, driver->id);
}


