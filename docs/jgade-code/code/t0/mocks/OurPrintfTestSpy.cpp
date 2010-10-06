//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C"
{
#include "OurPrintf.h"
#include "OurPrintfSpy.h"
}

TEST_GROUP(OurPrintfSpy)
{
    void setup()
    {
        UT_PTR_SET(OurPrintf, OurPrintf_spy);
    }

    void teardown()
    {
    }
};

TEST(OurPrintfSpy, testHelloWorld)
{
    char buffer[20];
    OurPrintf_spy_setBuffer(buffer, sizeof(buffer));
    OurPrintf("Hello, World\n");
    STRCMP_EQUAL("Hello, World\n", buffer);
}

TEST(OurPrintfSpy, testLimitTheOutputBufferSize)
{
    char buffer[5];
    OurPrintf_spy_setBuffer(buffer, sizeof(buffer));
    OurPrintf("Hello, World\n");
    STRCMP_EQUAL("Hell", buffer);
}

TEST(OurPrintfSpy, testPrintMultipleTimes)
{
    char buffer[25];
    OurPrintf_spy_setBuffer(buffer, sizeof(buffer));
    OurPrintf("Hello");
    OurPrintf(", World\n");
    STRCMP_EQUAL("Hello, World\n", buffer);
}

TEST(OurPrintfSpy, testPrintMultipleTimesnoBufferOverflow)
{
    char buffer[10];
    buffer[9] = 'x';
    OurPrintf_spy_setBuffer(buffer, sizeof(buffer)-1);
    OurPrintf("12345");
    OurPrintf("67890");
    STRCMP_EQUAL("12345678", buffer);
    BYTES_EQUAL('x', buffer[9]);
}



