//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_MockC2414FlashReadAndWrite_H
#define D_MockC2414FlashReadAndWrite_H

#include "c2414FlashReadAndWrite.h"

void Reset_FlashRead_and_FlashWrite();
void Expect_FlashWrite(udword udAddrOff, uCPUBusType ucVal);
void Expect_FlashRead(udword udAddrOff, uCPUBusType ucVal);
void Check_FlashWrite_Expectations();

#endif
