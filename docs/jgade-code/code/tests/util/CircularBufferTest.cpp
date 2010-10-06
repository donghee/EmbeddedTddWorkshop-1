//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
#include "FormatOutputSpy.h"
}

TEST_GROUP(CircularBuffer)
{
    CircularBuffer* buffer;

    void setup()
    {
      buffer = CircularBuffer_Create(10);
    }

    void teardown()
    {
       CHECK(CircularBuffer_VerifyIntegrity(buffer));
       CircularBuffer_Destroy(buffer);
    }

    void putManyInTheBuffer(int seed, int howMany)
    {
        for (int i = 0; i < howMany; i++)
            CircularBuffer_Put(buffer, i+seed);
    }
};

TEST(CircularBuffer, Create)
{
}
/* Copyright (c) 2007, 2008
 * James Grenning All Rights Reserved
 * Renaissance Software Consulting, Inc
 *
 * Contact info:
 * www.renaissancesoftware.net
 * www.renaissancesoftware.net/blog
 * james@renaissancesoftware.net
 */

TEST(CircularBuffer, EmptyAfterCreation)
{
    CHECK(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation)
{
    CHECK(!CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmpty)
{
    CircularBuffer_Put(buffer, 10046);
    CHECK(!CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotEmptyThenEmpty)
{
    CircularBuffer_Put(buffer, 4567);
    CHECK(!CircularBuffer_IsEmpty(buffer));
    CircularBuffer_Get(buffer);
    CHECK(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetPutOneValue)
{
    CircularBuffer_Put(buffer, 4567);
    LONGS_EQUAL(4567, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, GetPutAFew)
{
    CircularBuffer_Put(buffer, 1);
    CircularBuffer_Put(buffer, 2);
    CircularBuffer_Put(buffer, 3);
    LONGS_EQUAL(1, CircularBuffer_Get(buffer));
    LONGS_EQUAL(2, CircularBuffer_Get(buffer));
    LONGS_EQUAL(3, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Capacity)
{
    CircularBuffer* b = CircularBuffer_Create(2);
    LONGS_EQUAL(2, CircularBuffer_Capacity(b));
    CircularBuffer_Destroy(b);
}


TEST(CircularBuffer, IsFull)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i+100);

    CHECK(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, EmptyToFullToEmpty)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i+100);

    CHECK(CircularBuffer_IsFull(buffer));

    for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
        LONGS_EQUAL(j+100, CircularBuffer_Get(buffer));

    CHECK(CircularBuffer_IsEmpty(buffer));
    CHECK(!CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, WrapAround)
{
    int capacity = CircularBuffer_Capacity(buffer);
    for (int i = 0; i < capacity; i++)
        CircularBuffer_Put(buffer, i+100);

    CHECK(CircularBuffer_IsFull(buffer));
    LONGS_EQUAL(100, CircularBuffer_Get(buffer));
    CHECK(!CircularBuffer_IsFull(buffer));
    CircularBuffer_Put(buffer, 1000);
    CHECK(CircularBuffer_IsFull(buffer));

    for (int j = 1; j < capacity; j++)
        LONGS_EQUAL(j+100, CircularBuffer_Get(buffer));

    LONGS_EQUAL(1000, CircularBuffer_Get(buffer));
    CHECK(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, PutToFullThrows)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
    CHECK(!CircularBuffer_Put(buffer, 9999));
}

TEST(CircularBuffer, PutToFullDoesNotDamageContents)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

        CircularBuffer_Put(buffer, 9999);

    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        LONGS_EQUAL(i+900, CircularBuffer_Get(buffer));

    CHECK(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetFromEmptyReturns0)
{
    LONGS_EQUAL(0, CircularBuffer_Get(buffer));
}
