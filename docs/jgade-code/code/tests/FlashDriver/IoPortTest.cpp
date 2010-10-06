//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "IoPort.h"
    static uint16_t readValue = 0;
    static uint16_t writeValue = 0;

    uint16_t  FakeRead(IoPort*)
    {
        return readValue;
    }
    
    void  FakeWrite(IoPort*, uint16_t value)
    {
        writeValue = value;
    }
}

TEST_GROUP(IoPort)
{
    IoPort* ioPort;

    void setup()
    {
      ioPort = IoPort_Create(0xb000, "FakePort");
      readValue = 0xdead;
      writeValue = 0xdead;
      ioPort->Read = FakeRead;
      ioPort->Write = FakeWrite;;
    }
    
    void teardown()
    {
       IoPort_Destroy(ioPort);
    }
};

TEST(IoPort, FakeRead)
{
    LONGS_EQUAL(0xdead, ioPort->Read(ioPort));
}

TEST(IoPort, FakeWrite)
{
    ioPort->Write(ioPort, 0xbeef);
    LONGS_EQUAL(0xbeef, writeValue);
}

TEST(IoPort, GetName)
{
    STRCMP_EQUAL("FakePort", IoPort_GetName(ioPort));
}

