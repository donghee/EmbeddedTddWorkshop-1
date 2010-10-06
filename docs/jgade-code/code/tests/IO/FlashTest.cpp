//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


extern "C"
{
#include "Flash.h"
#include "MockIO.h"
#include "m28w160ect.h"
}

#include "CppUTest/TestHarness.h"

//START: ProgramSucceedsReadyImmediately_Refactored_TestGroup
TEST_GROUP(Flash)
{
    ioAddress_t address;
    ioData_t data;
    int result;

    void setup()
    {
        address = 0x1000;
        data = 0xBEEF;
        result = -1;

        MockIO_Create(10);
        Flash_Create();
    }

    void teardown()
    {
        Flash_Destroy();
        MockIO_Verify_Complete();
        MockIO_Destroy();
    }
};

//END: ProgramSucceedsReadyImmediately_Refactored_TestGroup

#if 0 //START: ProgramSucceedsReadyImmediately
TEST(Flash, ProgramSucceedsReadyImmediately)
{
    int result = 0;
    MockIO_Expect_Write(0, 0x40);
    MockIO_Expect_Write(0x1000, 0xBEEF);
    MockIO_Expect_Read(0, 1<<7);
    MockIO_Expect_Read(0x1000, 0xBEEF);

    result = Flash_Program(0x1000, 0xBEEF);

    LONGS_EQUAL(0, result);
    MockIO_Verify_Complete();
}

//END: ProgramSucceedsReadyImmediately
#endif

//START: ProgramSucceedsReadyImmediately_Refactored_Test
TEST(Flash, ProgramSucceedsReadyImmediately)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit);
    MockIO_Expect_Read(address, data);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashSuccess, result);
}
//END: ProgramSucceedsReadyImmediately_Refactored_Test

//START: ProgramSucceedsNotImmediatelyReady
TEST(Flash, ProgramSucceedsNotImmediatelyReady)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, 0);
    MockIO_Expect_Read(StatusRegister, 0);
    MockIO_Expect_Read(StatusRegister, 0);
    MockIO_Expect_Read(StatusRegister, ReadyBit);
    MockIO_Expect_Read(address, data);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashSuccess, result);
}
//END: ProgramSucceedsNotImmediatelyReady

//START: ProgramFails_VppError
TEST(Flash, ProgramFails_VppError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit | VppErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashVppError, result);
}
//END: ProgramFails_VppError

//START: ProgramFails_ProgramError
TEST(Flash, ProgramFails_ProgramError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit | ProgramErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashProgramError, result);
}
//END: ProgramFails_ProgramError

//START: ProgramFails_ProtectedBlockError
TEST(Flash, ProgramFails_ProtectedBlockError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit | BlockProtectionErrorBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashProgramProtectedBlockError, result);
}
//END: ProgramFails_ProtectedBlockError

//START: ProgramFails_FlashUnknownProgramError
TEST(Flash, ProgramFails_FlashUnknownProgramError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit |  EraseSuspendBit | EraseErrorBit | ProgramSuspendBit | ReservedBit);
    MockIO_Expect_Write(CommandRegister, Reset);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashUnknownProgramError, result);
}
//END: ProgramFails_FlashUnknownProgramError

//START: ProgramFails_FlashReadBackError
TEST(Flash, ProgramFails_FlashReadBackError)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ReadyBit);
    MockIO_Expect_Read(address, data-1);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashReadBackError, result);
}
//END: ProgramFails_FlashReadBackError

//START: ProgramSucceeds_IgnoresOtherBitsUntilReady
TEST(Flash, ProgramSucceeds_IgnoresOtherBitsUntilReady)
{
    MockIO_Expect_Write(CommandRegister, ProgramCommand);
    MockIO_Expect_Write(address, data);
    MockIO_Expect_Read(StatusRegister, ~ReadyBit);
    MockIO_Expect_Read(StatusRegister, ReadyBit);
    MockIO_Expect_Read(address, data);

    result = Flash_Program(address, data);

    LONGS_EQUAL(FlashSuccess, result);
}
//END: ProgramSucceeds_IgnoresOtherBitsUntilReady

