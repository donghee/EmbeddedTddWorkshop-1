//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net

//START: initialization
#include "Utils.h"

static int FormatOutput_Impl(const char * format, ...)
{
    //snip
    //END: initialization
    return 1;
    //START: initialization
}

int (*FormatOutput)(const char* format, ...) = FormatOutput_Impl;
//END: initialization
