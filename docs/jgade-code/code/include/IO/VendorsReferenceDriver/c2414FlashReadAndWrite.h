//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_c2414FlashReadAndWrite_H
#define D_c2414FlashReadAndWrite_H

#include "c2414.h"

uCPUBusType  FlashRead( udword udAddrOff );
void  FlashWrite( udword udAddrOff, uCPUBusType ucVal );

#endif

//Original code thanks to STMicroelectronics.

