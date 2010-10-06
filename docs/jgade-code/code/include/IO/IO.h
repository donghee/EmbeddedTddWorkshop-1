//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


//START: include
#ifndef D_IO_H
#define D_IO_H
#include <stdint.h>

typedef uint32_t ioAddress_t;
typedef uint16_t ioData_t;

ioData_t IO_Read(ioAddress_t offset);
void  IO_Write(ioAddress_t offset, ioData_t data);

#endif
//END: include

//Original code thanks to STMicroelectronics.

