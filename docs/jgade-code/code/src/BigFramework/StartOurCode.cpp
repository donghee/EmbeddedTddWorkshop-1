//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * StartOurCode.cpp
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#include "StartOurCode.h"
#include "OurCode.h"
#include "BFwAdaptor.h"

StartOurCode::StartOurCode()
{
    BFwAdaptor a;
    OurCode OurCode(&a);
    OurCode.doMyThing();
    //and the system runs
}

StartOurCode::~StartOurCode()
{
}
