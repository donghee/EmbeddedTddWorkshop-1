//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "Flash.h"
#include "IO.h"
#include "m28w160ect.h"
//static local variables


void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

#if 0 //START: ProgramSucceedsReadyImmediately_Refactored
int Flash_Program(ioAddress_t address, ioData_t data)
{
    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);
    IO_Read(StatusRegister);
    IO_Read(address);
    return FlashSuccess;
}
//END: ProgramSucceedsReadyImmediately_Refactored
#endif

#if 0 //START: AddedFlashProgramLoop
int Flash_Program(ioAddress_t address, ioData_t data)
{
    ioData_t status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    IO_Read(address);

    return FlashSuccess;
}
//END: AddedFlashProgramLoop
#endif

//START: programError
static inline int programError(int status)
{
    IO_Write(CommandRegister, Reset);

    if (status & VppErrorBit)
        return FlashVppError;
    else if (status & ProgramErrorBit)
        return FlashProgramError;
    else if (status & BlockProtectionErrorBit)
        return FlashProgramProtectedBlockError;
    else
        return FlashUnknownProgramError;
}
//END: programError

//START: AddedFlashProgramLoopAllErrorsHandled
int Flash_Program(ioAddress_t offset, ioData_t data)
{
    ioData_t status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(offset, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    if (status != ReadyBit)
        return programError(status);

    if (data != IO_Read(offset))
        return FlashReadBackError;

    return FlashSuccess;
}
//END: AddedFlashProgramLoopAllErrorsHandled
