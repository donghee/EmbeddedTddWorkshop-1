//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_FakeC2414FlashReadAndWrite_H
#define D_FakeC2414FlashReadAndWrite_H

#include "c2414ReadAndWrite.h"

void Reset_FlashRead_and_FlashWrite();
void GetLast_FlashWrite_Address();
void GetLast_FlashWrite_Value();
void GetLast_FlashRead_Address();
void Set_FlashRead_Value(uCPUBusType ucVal);

#endif
