/*
 * testunity_fixture.c
 *
 *  Created on: Apr 15, 2010
 *      Author: james
 */

#include "unity_fixture.h"

static int data = -1;

TEST_GROUP(mygroup);

TEST_SETUP(mygroup)
{
    data = 0;
}

TEST_TEAR_DOWN(mygroup)
{
    data = -1;
}

TEST(mygroup, test1)
{
    TEST_ASSERT_EQUAL_INT(0, data);
}

TEST(mygroup, test2)
{
    TEST_ASSERT_EQUAL_INT(0, data);
}

TEST(mygroup, test3)
{
    TEST_ASSERT_EQUAL_INT(0, data);
}
