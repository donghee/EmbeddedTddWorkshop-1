//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include <memory.h>
}

//START: testGroup
TEST_GROUP(sprintf)
{
    char buffer[100];
    const char * expected;
    int length;

    void setup()
    {
        memset(buffer, 0xaa, sizeof(buffer));
        expected = "";
        length = 0;
    }

    void teardown()
    {
    }

    void expect(const char * s)
    {
        expected = s;
    }

    void given(int charsWritten)
    {
        length = charsWritten;
        LONGS_EQUAL(strlen(expected), length);
        STRCMP_EQUAL(expected, buffer);
        BYTES_EQUAL(0xaa, buffer[strlen(expected) + 1]);
    }


};
//END: testGroup

#if 1 //START: RefactoredTests
TEST(sprintf, NoFormatOperations)
{
    expect("hey");
    given(sprintf(buffer, "hey"));
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    given(sprintf(buffer, "%s\n", "Hello World"));
}
//END: RefactoredTests

#else //START: Duplication
//START: FormatSpace
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];
    memset(buffer, 0xaa, sizeof(buffer));

    LONGS_EQUAL(3, sprintf(buffer, "hey"));
    STRCMP_EQUAL("hey", buffer);
    BYTES_EQUAL(0xaa, buffer[2]);
}
//END: FormatSpace

TEST(sprintf, InsertString)
{
    char buffer[20];
    memset(buffer, 0xaa, sizeof(buffer));

    LONGS_EQUAL(12, sprintf(buffer, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", buffer);
    BYTES_EQUAL(0xaa, buffer[13]);
}
//END: Duplication
#endif

#if 0 //START: NoFormatOperations1
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];

    LONGS_EQUAL(3, sprintf(buffer, "hey"));
    STRCMP_EQUAL("hey", buffer);
}
//END: NoFormatOperations1
#endif

#if 0 //START: NoFormatOperations2
TEST(sprintf, NoFormatOperations)
{
    char buffer[5] = "";

    LONGS_EQUAL(3, sprintf(buffer, "hey"));
    STRCMP_EQUAL("hey", buffer);
}
//END: NoFormatOperations2
#endif


#if 0 //START: oneString
TEST(sprintf, InsertString)
{
    char buffer[20] = "";

    LONGS_EQUAL(12, sprintf(buffer, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", buffer);
}
//END: oneString
#endif

#if 0 //START: failingTest
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];

    LONGS_EQUAL(2, sprintf(buffer, "hey"));
    STRCMP_EQUAL("hey", buffer);
}
#endif //END: failingTest

