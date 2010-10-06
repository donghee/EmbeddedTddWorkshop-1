//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "TimeService.h"
#include "common.h"

//static local variables

void TimeService_Create(void)
{
	//OS dependent init
	explodesInTestEnvironment();
}

void TimeService_Destroy()
{
	//OS dependent cleanup
	explodesInTestEnvironment();
}

int TimeService_GetMinute(void)
{
	//OS dependent get minute
	explodesInTestEnvironment();
	return 0;
}

int TimeService_GetDay(void)
{
	//OS dependent get day
	explodesInTestEnvironment();
	return 0;
}
