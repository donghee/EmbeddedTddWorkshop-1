//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "unity_fixture.h"
#include "unity_output_Spy.h"
#include <stdlib.h>
#include <string.h>

TEST_GROUP(UnityOutput)

TEST_SETUP(UnityOutput)
{

}

TEST_TEAR_DOWN(UnityOutput)
{

}

TEST(UnityOutput, UnityOutputCharSpy)
{
    UnityOutputCharSpy_Create(20);
    outputChar = UnityOutputCharSpy_OutputChar;
    UnityPrint("Hello World");
    outputChar = putchar;
    TEST_ASSERT_EQUAL_STRING("Hello World", UnityOutputCharSpy_Get());
    UnityOutputCharSpy_Destroy();
}

TEST(UnityOutput, UnityOutputCharSpyFullBuffer)
{
    UnityOutputCharSpy_Create(5);
    outputChar = UnityOutputCharSpy_OutputChar;
    UnityPrint("Hello World");
    outputChar = putchar;
    TEST_ASSERT_EQUAL_STRING("Hell", UnityOutputCharSpy_Get());
    UnityOutputCharSpy_Destroy();
}



