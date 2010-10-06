//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_Flash_H
#define D_Flash_H

///////////////////////////////////////////////////////////////////////////////
//
//  Flash is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "IO.h"

void Flash_Create(void);
void Flash_Destroy(void);
int Flash_Program(ioAddress_t offset, ioData_t data);

typedef enum
{
	FlashSuccess = 0,
	FlashVppError,
	FlashProgramError,
	FlashProgramProtectedBlockError,
	FlashUnknownProgramError,
	FlashReadBackError
} FlashStatus;
#endif  // D_Flash_H
