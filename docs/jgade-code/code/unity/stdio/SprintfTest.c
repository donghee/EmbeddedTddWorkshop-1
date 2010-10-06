//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "unity_fixture.h"
#include <stdio.h>
#include <memory.h>

//START: testGroup
TEST_GROUP(sprintf)

static char buffer[100];
static const char * expected;
static int length;

TEST_SETUP(sprintf)
{
    memset(buffer, 0xaa, sizeof(buffer));
    expected = "";
    length = 0;
}

TEST_TEAR_DOWN(sprintf)
{
}

static void expect(const char * s)
{
    expected = s;
}

static void given(int charsWritten)
{
    TEST_ASSERT_EQUAL(strlen(expected), charsWritten);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_BYTES_EQUAL(0xaa, buffer[strlen(expected) + 1]);
}

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
#endif  //END: RefactoredTests

//to run this also change in SprintfTestRunner.c
#if 0 //START: failingTest
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];

    TEST_ASSERT_EQUAL(3, sprintf(buffer, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", buffer);
}
//END: failingTest
#endif

#if 0 //START: Duplication
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];
    memset(buffer, 0xaa, sizeof(buffer));

    TEST_ASSERT_EQUAL(3, sprintf(buffer, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", buffer);
    TEST_ASSERT_BYTES_EQUAL(0xaa, buffer[4]);
}

TEST(sprintf, InsertString)
{
    char buffer[20];
    memset(buffer, 0xaa, sizeof(buffer));

    TEST_ASSERT_EQUAL(12, sprintf(buffer, "%s\n", "Hello World"));
    TEST_ASSERT_EQUAL_STRING("Hello World\n", buffer);
    TEST_ASSERT_BYTES_EQUAL(0xaa, buffer[13]);
}
//END: Duplication
#endif

#if 0 //START: NoFormatOperations1
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];

    TEST_ASSERT_EQUAL(3, sprintf(buffer, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", buffer);
}
//END: NoFormatOperations1
#endif

#if 0 //START: NoFormatOperations2
TEST(sprintf, NoFormatOperations)
{
    char buffer[5] = "";
    TEST_ASSERT_EQUAL(3, sprintf(buffer, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", buffer);
}
//END: NoFormatOperations2
#endif

#if 0 //START: NoFormatOperations3
TEST(sprintf, NoFormatOperations)
{
    char buffer[5];
    memset(buffer, 0xaa, sizeof(buffer));

    TEST_ASSERT_EQUAL(3, sprintf(buffer, "hey"));
    TEST_ASSERT_EQUAL_STRING("hey", buffer);
}
//END: NoFormatOperations3
#endif


#if 0 //START: oneString
TEST(sprintf, InsertString)
{
    char buffer[20] = "";

    TEST_ASSERT_EQUAL(12, sprintf(buffer, "%s\n", "Hello World"));
    TEST_ASSERT_EQUAL_STRING("Hello World\n", buffer);
}
//END: oneString
#endif
