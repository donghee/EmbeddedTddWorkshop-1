//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include <string.h>
#include <stdio.h>
#include "c2414.h"
#include "CppUTest/TestHarness_c.h"

#define FLASH_READ 1
#define FLASH_WRITE 2

typedef struct RwExpectation {
    int kind;
    udword addr;
    uCPUBusType value;
} RwExpectation;

static RwExpectation rwExpectations[20];
static int setExpectationCount;
static int getExpectationCount;

void Reset_FlashRead_and_FlashWrite() {
    memset(rwExpectations, 0, sizeof(rwExpectations));
    setExpectationCount = 0;
    getExpectationCount = 0;
}

void Expect_FlashWrite(udword addr, uCPUBusType value) {
    rwExpectations[setExpectationCount].kind = FLASH_WRITE;
    rwExpectations[setExpectationCount].addr = addr;
    rwExpectations[setExpectationCount].value = value;
    setExpectationCount++;
}

void Expect_FlashRead(udword addr, uCPUBusType value) {
    rwExpectations[setExpectationCount].kind = FLASH_READ;
    rwExpectations[setExpectationCount].addr = addr;
    rwExpectations[setExpectationCount].value = value;
    setExpectationCount++;
}

void checkExpectationCount() {
    if (getExpectationCount >= setExpectationCount) {
        FAIL_TEXT_C("Not enough expectations set");
    }
}

uCPUBusType FlashRead( udword addr ) {
    uCPUBusType result = 0xff;
    char buffer[100];
    udword expectedAddr =  rwExpectations[getExpectationCount].addr;

    checkExpectationCount();
    if (FLASH_READ != rwExpectations[getExpectationCount].kind) {
        FAIL_TEXT_C("Unexpected READ");
    }
    else {
        if (expectedAddr != addr ) {
            sprintf(buffer, "Expectation #%d: Expected read 0x%x\n"
                            "                           But got 0x%x",
            getExpectationCount+1, expectedAddr, addr);
            FAIL_TEXT_C(buffer);
        }
        result = rwExpectations[getExpectationCount].value;
        getExpectationCount++;
    }

    return result;
}

void FlashWrite( udword addr, uCPUBusType value ) {

    char buffer[100];
    udword expectedAddr = rwExpectations[getExpectationCount].addr;
    uCPUBusType expectedValue = rwExpectations[getExpectationCount].value;

    checkExpectationCount();
    if (FLASH_WRITE != rwExpectations[getExpectationCount].kind) {
        sprintf(buffer, "Expectation #%d: Unexpected write to 0x%x=0x%x",
                getExpectationCount+1, addr, value);
        FAIL_TEXT_C(buffer);
    }
    else {
        if (expectedAddr != addr || expectedValue != value) {
            sprintf(buffer, "Expectation #%d: Expected write 0x%x=0x%x\n"
                            "                           But got 0x%x=0x%x",
            getExpectationCount+1, expectedAddr, expectedValue, addr, value);
            FAIL_TEXT_C(buffer);
        }
    getExpectationCount++;
    }
}

void Check_FlashWrite_Expectations() {
    char buffer[100];
    if (getExpectationCount == setExpectationCount)
        return;

    sprintf(buffer, "Expected %d reads/writes but got %d",
               setExpectationCount, getExpectationCount);
    FAIL_TEXT_C(buffer);

}
