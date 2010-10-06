//- Copyright (c) 2008-2009 James Grenning
//- All rights reserved
//- For use by participants in James' training courses.


//START: MockIO.h
#ifndef D_MockIO_H
#define D_MockIO_H

#include "IO.h"

void MockIO_Create(int maxExpectations);
void MockIO_Destroy();
void MockIO_Expect_Write(ioAddress_t offset, ioData_t data);
void MockIO_Expect_Read(ioAddress_t  offset, ioData_t returnData);
void MockIO_Verify_Complete();

#endif
//END: MockIO.h
