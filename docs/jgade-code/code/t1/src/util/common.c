//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "common.h"
#include <assert.h>

void explodesInTestEnvironment()
{
	assert(0 == "Explode - intercepted call that cannot be made in test environment");
}