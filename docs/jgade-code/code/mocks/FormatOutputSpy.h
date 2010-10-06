//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_FormatOutputSpy_H
#define D_FormatOutputSpy_H


//START: interface
#include "Utils.h"

int FormatOutputSpy(const char * format, ...);
void FormatOutputSpy_Create(int size);
void FormatOutputSpy_Destroy();
const char * FormatOutputSpy_GetOutput();
//END: interface

#endif  // D_FormatOutput_H
