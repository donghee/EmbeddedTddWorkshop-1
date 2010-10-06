//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#ifndef D_RandomMinute_H
#define D_RandomMinute_H

///////////////////////////////////////////////////////////////////////////////
//
//  RandomMinute is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

void RandomMinute_Create(int bound);
extern int (*RandomMinute_Get)();

#endif  // D_RandomMinute_H
