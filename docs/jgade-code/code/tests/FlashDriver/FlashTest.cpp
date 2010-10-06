//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C" {
#include "MockC2414ReadAndWrite.h"
}

//START: BetterInitialTest
TEST_GROUP(Flash)
{
    enum  {
        eraseBlock = 0x20,
        writeEraseConfirm = 0xD0,
        blockNumber = 4,
        flashDone = 1<<7,
        flashNotDone = 0,
        vppError = 1<<3,
        commandSequenceError = 1<<4 | 1<<5,
        eraseError = 1<<5,
        writeToProtectedBlock = 1,
        clearStatusWord = 0x50,
    };

    void setup()
    {
        Reset_FlashRead_and_FlashWrite();
    }
    void teardown()
    {
    }
};
//END: BetterInitialTest

#if 0
//START: InitialFlashTest
TEST(Flash, CheckCfiCommand)
{
    ParameterType p;
    ReturnType result;
    Reset_FlashRead_and_FlashWrite();
        
    result = Flash(ReadCfi, &p);
    
    LONGS_EQUAL(Flash_Success, result);
}
//END: InitialFlashTest
#endif

#if 0
//START: InitialFlashTest
TEST(Flash, CheckCfiCommand)
{        
    FlashWrite(0x55, 0x98);
    CHECK( 'Q' == FlashRead(0x10);
    CHECK( 'R' == FlashRead(0x11);
    CHECK( 'Y' == FlashRead(0x12);
}
//END: InitialFlashTest
#endif
//START: BetterInitialTest
TEST(Flash, CheckCfiCommand)
{
    ParameterType p;
    ReturnType result;
    
    p.ReadCfi.uwCfiFunc = 0x24;
    
    Expect_FlashWrite(0x0, 0x98); 
    Expect_FlashRead(0x10, 'Q'); 
    Expect_FlashRead(0x11, 'R'); 
    Expect_FlashRead(0x12, 'Y'); 
    Expect_FlashRead(p.ReadCfi.uwCfiFunc, 0xAA); 
    Expect_FlashWrite(0x0, 0xff); 
    
    result = Flash(ReadCfi, &p);
    
    LONGS_EQUAL(Flash_Success, result);
    LONGS_EQUAL(0xAA, p.ReadCfi.ucCfiValue);
    Check_FlashWrite_Expectations();
}
//END: BetterInitialTest

//START: EraseBlockTest
TEST(Flash, EraseBlockHappyPath)
{    
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], writeEraseConfirm); 
    Expect_FlashRead(0x0, flashNotDone);
    Expect_FlashRead(0x0, flashNotDone);
    Expect_FlashRead(0x0, flashDone);
    Expect_FlashWrite(0x0, clearStatusWord); 
    
    ReturnType result = MyFlashBlockErase(blockNumber);
    
    LONGS_EQUAL(Flash_Success, result);
    Check_FlashWrite_Expectations();
}
//END: EraseBlockTest

//START: EraseBlockVppError
TEST(Flash, EraseBlockVppError)
{
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], writeEraseConfirm); 
    Expect_FlashRead(0x0, flashDone | vppError);
    Expect_FlashWrite(0x0, clearStatusWord); 
    
    ReturnType result = MyFlashBlockErase(blockNumber);
    
    LONGS_EQUAL(Flash_VppInvalid, result);
    Check_FlashWrite_Expectations();
}
//END: EraseBlockVppError

//START: EraseBlockCommandSequenceErrorDetected
TEST(Flash, EraseBlockCommandSequenceErrorDetected)
{
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], writeEraseConfirm); 
    Expect_FlashRead(0x0, flashDone | commandSequenceError);
    Expect_FlashWrite(0x0, clearStatusWord); 
    
    ReturnType result = MyFlashBlockErase(blockNumber);
    
    LONGS_EQUAL(Flash_BlockEraseFailed, result);
    Check_FlashWrite_Expectations();
}
//END: EraseBlockCommandSequenceErrorDetected

//START: EraseError
TEST(Flash, EraseError)
{
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], writeEraseConfirm); 
    Expect_FlashRead(0x0, flashDone | eraseError);
    Expect_FlashWrite(0x0, clearStatusWord); 
    
    ReturnType result = MyFlashBlockErase(blockNumber);
    
    LONGS_EQUAL(Flash_BlockEraseFailed, result);
    Check_FlashWrite_Expectations();
}
//END: EraseError

//START: WriteToProtectedBlock
TEST(Flash, WriteToProtectedBlock)
{
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], writeEraseConfirm); 
    Expect_FlashRead(0x0, flashDone | writeToProtectedBlock);
    Expect_FlashWrite(0x0, clearStatusWord); 
    
    ReturnType result = MyFlashBlockErase(blockNumber);
    
    LONGS_EQUAL(Flash_BlockProtected, result);
    Check_FlashWrite_Expectations();
}
//END: WriteToProtectedBlock
//START: EraseBlockTest
TEST(Flash, EraseBlockHappyPath2)
{
    ParameterType p;
    ReturnType result;
    
    int eraseBlock = 0x20;
    int blockNumber = 4;
    int flashDone = 1<<7;
    int flashBusy = 0;
    int clearStatusWord = 0x50;
    
    Expect_FlashWrite(0x0, clearStatusWord); 
    Expect_FlashWrite(0x0, eraseBlock); 
    Expect_FlashWrite(BlockOffset[blockNumber], 0xD0); 
    Expect_FlashRead(0x0, flashBusy); 
    Expect_FlashRead(0x0, flashBusy); 
    Expect_FlashRead(0x0, flashBusy); 
    Expect_FlashRead(0x0, flashDone);
    Expect_FlashWrite(0x0, 0xff); 
    
    p.BlockErase.ublBlockNr = blockNumber;
    result = Flash(BlockErase, &p);
    
    LONGS_EQUAL(Flash_Success, result);
    Check_FlashWrite_Expectations();
}
//END: EraseBlockTest
