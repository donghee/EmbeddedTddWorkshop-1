//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_OurPrintfSpy_H
#define D_OurPrintfSpy_H

#include "OurPrintf.h"

int OurPrintf_spy(const char* format, ...);
void OurPrintf_spy_setBuffer(char* buffer, int size);

#endif  // D_OurPrintf_H
