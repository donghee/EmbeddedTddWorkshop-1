//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "unity_fixture.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"


//START:final
//START: FirstThreeTests
TEST_GROUP(LedDriver)

static uint16_t virtualLeds;

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}
//END: FirstThreeTests

//START: FirstThreeTests
//START: LedsAreOffAfterInitialization
TEST(LedDriver, LedsOffAfterInitialization)
{
    virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: LedsAreOffAfterInitialization

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: FirstThreeTests

//START: TurnOnMultipleLeds
TEST(LedDriver, TurnOnMultipleLeds)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}
//END: TurnOnMultipleLeds

//START: TurnOffMultipleLeds
TEST(LedDriver, TurnOffMultipleLeds)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(9);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180)&0xffff, virtualLeds);
}
//END: TurnOffMultipleLeds

//START: TurnOffAnyLedSecondTry
TEST(LedDriver, TurnOffAnyLed)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}
//END: TurnOffAnyLedSecondTry

//START: LedMemoryIsNotReadable
TEST(LedDriver, LedMemoryIsNotReadable)
{
    virtualLeds = 0xffff;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}
//END: LedMemoryIsNotReadable

//START: UpperAndLowerBounds
TEST(LedDriver, UpperAndLowerBounds)
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}
//END: UpperAndLowerBounds

//START: OutOfBoundsTurnOnDoesNoHarm
TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);

    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: OutOfBoundsTurnOnDoesNoHarm

//START: OutOfBoundsTurnOffDoesNoHarm
TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnAllOn();

    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);

    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
//END: OutOfBoundsTurnOffDoesNoHarm

//START: OutOfBoundsToDo
IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
    //TODO: what should we do during runtime?
}
//END: OutOfBoundsToDo

//START: OutOfBoundsProducesRuntimeError
TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
            RuntimeErrorStub_GetLastError());
}
//END: OutOfBoundsProducesRuntimeError

//START: IsOn
TEST(LedDriver, IsOn)
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}
//END: IsOn

//START: IsOff
TEST(LedDriver, IsOff)
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(12));
    LedDriver_TurnOn(12);
    TEST_ASSERT_FALSE(LedDriver_IsOff(12));
}
//END: IsOff

//START: OutOfBoundsLedsAreAlwaysOff2
TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsOff(17));
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}
//END: OutOfBoundsLedsAreAlwaysOff2

//START: TurnAllOn
TEST(LedDriver, AllOn)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
//END: TurnAllOn

//START: TurnAllOff
TEST(LedDriver, AllOff)
{
    LedDriver_TurnAllOn();
    LedDriver_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: TurnAllOff
//END: final

/*
 * Intermediate examples below this comment
 */

#if 0 //START: TurnOnLedZero
TEST(LedDriver, TurnOnLedOne)
{
    uint16_t virtualLeds;
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}
//END: TurnOnLedZero

//START: TurnOffLedOne
TEST(LedDriver, TurnOffLedOne)
{
    uint16_t virtualLeds;
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
#endif //END: TurnOffLedOne



#if 0 //START: TurnAllOnRevised
TEST(LedDriver, AllOn)
{
    LedDriver_TurnAllOn();
    TEST_ASSERT_TRUE(LedDriver_IsOn(1));
    TEST_ASSERT_TRUE(LedDriver_IsOn(8));
    TEST_ASSERT_TRUE(LedDriver_IsOn(16));
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
#endif END: TurnAllOnRevised


#if 0
//START: TurnOffAnyLedFirstTry
TEST(LedDriver, TurnOffAnyLed)
{
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0x100, virtualLeds);
}
//END: TurnOffAnyLedFirstTry

//START: RevisedTestGroupPlusCreate
TEST(LedDriver, LedsOffAfterInitialization)
{
    virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: RevisedTestGroupPlusCreate
//START: OutOfBoundsChangesNothing
TEST(LedDriver, OutOfBoundsChangesNothing)
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);

    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: OutOfBoundsChangesNothing
//START: Led3141
TEST(LedDriver, OutOfBoundsChangesNothing)
{
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_TurnOn(0);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_TurnOn(17);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_TurnOn(33);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
    LedDriver_TurnOn(3141);

    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: Led3141
//START: OutOfBoundsTurnOffDoesNoHarm1
TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);

    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
//END: OutOfBoundsTurnOffDoesNoHarm1
//START: OutOfBoundsTurnOffDoesNoHarm2
TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnAllOn();

    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);

    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
//END: OutOfBoundsTurnOffDoesNoHarm2

//START: OutOfBoundsLedsAreAlwaysOff1
TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
}
//END: OutOfBoundsLedsAreAlwaysOff1
#endif

#if 0 //START: StartingPoint
#include "unity_fixture.h"

TEST_GROUP(LedDriver)

TEST_SETUP(LedDriver)
{
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, LedsOffAfterInitialization)
{
    TEST_FAIL("Start here");
}
//END: StartingPoint

//START: NoFailStartingPoint
TEST_GROUP(LedDriver)

TEST_SETUP(LedDriver)
{
}

TEST_TEAR_DOWN(LedDriver)
{
}


TEST(LedDriver, LedsOffAfterInitialization)
{
}
//END: NoFailStartingPoint

#endif
