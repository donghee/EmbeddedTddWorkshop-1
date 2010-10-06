//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.

//START: full
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "MockIO.h"
#include "CppUTest/TestHarness_c.h"

enum
{
    FLASH_READ, FLASH_WRITE, NoExpectedValue = -1
};

//START: Data
typedef struct Expectation
{
    int kind;
    ioAddress_t addr;
    ioData_t value;
} Expectation;

static Expectation * expectations = 0;
static int setExpectationCount;
static int getExpectationCount;
static int maxExpectationCount;
static int failureAlreadyReported = 0;
//END: Data

static Expectation expected;
static Expectation actual;

static char * report_expect_write_was_read =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Read(0x%x)";
static char * report_read_wrong_address =
    "Expected IO_Read(0x%x) returns 0x%x;\n"
    "\t        But was IO_Read(0x%x)";
static char * report_expect_read_was_write =
    "Expected IO_Read(0x%x) would return 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static char * report_write_does_not_match =
    "Expected IO_Write(0x%x, 0x%x)\n"
    "\t        But was IO_Write(0x%x, 0x%x)";
static char * report_too_many_write_expectations =
    "MockIO_Expect_IO_Write: Too many expectations";
static char * report_too_many_read_expectations =
    "MockIO_Expect_IO_Read: Too many expectations";
static char * report_MockIO_not_initialized =
    "MockIO not initialized, call MockIO_Create()";
static char * report_write_but_out_of_expectations =
    "IO_Write(0x%x, 0x%x)";
static char * report_read_but_out_of_expectations =
    "IO_Read(0x%x)";
static const char * report_no_more_expectations =
    "R/W %d: No more expectations but was ";
static const char * report_expectation_number =
    "R/W %d: ";

//START: CreateDestroy
void MockIO_Create(int maxExpectations)
{
    expectations = malloc(sizeof(Expectation)*maxExpectations);
    memset(expectations, 0, sizeof(expectations));
    setExpectationCount = 0;
    getExpectationCount = 0;
    maxExpectationCount = maxExpectations;
    failureAlreadyReported = 0;
}

void MockIO_Destroy()
{
    if (expectations)
        free(expectations);
    expectations = 0;
}
//END: CreateDestroy

static void fail(char * message)
{
    failureAlreadyReported = 1;
    FAIL_TEXT_C(message);
}

//START: MockIO_Expect_IO_Write_IO_Read_Helpers
static void failWhenNotInitialized()
{
    if (expectations == 0)
        fail(report_MockIO_not_initialized);
}

static void failWhenNoRoomForExpectations(char * message)
{
    failWhenNotInitialized();
    if (setExpectationCount >= maxExpectationCount)
        fail(message);
}

void recordExpectation(int kind, ioAddress_t addr, ioData_t data)
{
    expectations[setExpectationCount].kind = kind;
    expectations[setExpectationCount].addr = addr;
    expectations[setExpectationCount].value = data;
    setExpectationCount++;
}
//END: MockIO_Expect_IO_Write_IO_Read_Helpers

//START: MockIO_Expect_Functions
void MockIO_Expect_Write(ioAddress_t addr, ioData_t value)
{
    failWhenNoRoomForExpectations(report_too_many_write_expectations);
    recordExpectation(FLASH_WRITE, addr, value);
}

void MockIO_Expect_Read(ioAddress_t addr, ioData_t value)
{
    failWhenNoRoomForExpectations(report_too_many_read_expectations);
    recordExpectation(FLASH_READ, addr, value);
}
//END: MockIO_Expect_Functions

static void failWhenNoUnusedExpectations(char * format)
{
    char message[100];
    int size = sizeof(message) - 1;

    if (getExpectationCount >= setExpectationCount)
    {
        int offset = snprintf(message, size,
                report_no_more_expectations, getExpectationCount + 1);
        snprintf(message + offset, size - offset,
                format, actual.addr, actual.value);
        fail(message);
    }
}

static void setExpectedAndActual(ioAddress_t addr, ioData_t value)
{
    expected.addr = expectations[getExpectationCount].addr;
    expected.value = expectations[getExpectationCount].value;
    actual.addr = addr;
    actual.value = value;
}

static void failExpectation(char * expectationFailMessage)
{
    char message[100];
    int size = sizeof(message) - 1;
    int offset = snprintf(message, size,
            report_expectation_number, getExpectationCount + 1);
    snprintf(message + offset, size - offset,
            expectationFailMessage, expected.addr, expected.value,
            actual.addr, actual.value);
    fail(message);
}

static void failWhen(int condition, char * expectationFailMessage)
{
    if (condition)
        failExpectation(expectationFailMessage);
}

static int expectationIsNot(int kind)
{
    return kind != expectations[getExpectationCount].kind;
}

static int expectedAddressIsNot(ioAddress_t addr)
{
    return expected.addr != addr;
}

static int expectedDataIsNot(ioData_t data)
{
    return expected.value != data;
}

//START: IO_Write
void IO_Write(ioAddress_t addr, ioData_t value)
{
    setExpectedAndActual(addr, value);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_write_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_WRITE), report_expect_read_was_write);
    failWhen(expectedAddressIsNot(addr), report_write_does_not_match);
    failWhen(expectedDataIsNot(value), report_write_does_not_match);
    getExpectationCount++;
}
//END: IO_Write

//START: IO_Read
ioData_t IO_Read(ioAddress_t addr)
{
    setExpectedAndActual(addr, NoExpectedValue);
    failWhenNotInitialized();
    failWhenNoUnusedExpectations(report_read_but_out_of_expectations);
    failWhen(expectationIsNot(FLASH_READ), report_expect_write_was_read);
    failWhen(expectedAddressIsNot(addr), report_read_wrong_address);

    return expectations[getExpectationCount++].value;
}
//END: IO_Read

static void failWhenNotAllExpectationsUsed()
{
    char format[] = "Expected %d reads/writes but got %d";
    char message[sizeof(format)+5+5];

    if (getExpectationCount == setExpectationCount)
        return;

    snprintf(message, sizeof(message), format, setExpectationCount,
            getExpectationCount);
    fail(message);
}


//START: MockIO_Verify_Complete
void MockIO_Verify_Complete()
{
    if (failureAlreadyReported)
        return;
    failWhenNotAllExpectationsUsed();
}
//END: MockIO_Verify_Complete
//END: full
