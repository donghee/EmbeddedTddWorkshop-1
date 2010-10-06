//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#include "RandomMinute.h"
#include <stdlib.h>
#include <string.h>

//static local variables

static int bound = 0;

void RandomMinute_Create(int b)
{
    bound = b;
}

//From the .c file
int RandomMinute_GetImpl()
{
    return bound - rand() % (bound * 2 + 1);
}

int (*RandomMinute_Get)() = RandomMinute_GetImpl;

