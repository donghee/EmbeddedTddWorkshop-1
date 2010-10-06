//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "c2414.h"
#include "CppUTest/TestHarness_c.h"

#if 0
//START: InitialFlashTest
static unsigned char flashQueryStructure[0x40] = {0};

void Reset_FlashRead_and_FlashWrite() {
    memset(flashQueryStructure, 0, sizeof(flashQueryStructure));
}

uCPUBusType FlashRead( udword address ) {
    return flashQueryStructure[address];
}

void FlashWrite( udword address, uCPUBusType value ) {
    if (address == 0x55 && value == 0x98) {
        flashQueryStructure[0x10] = 'Q';
        flashQueryStructure[0x11] = 'R';
        flashQueryStructure[0x12] = 'Y';
    }
}
#endif

