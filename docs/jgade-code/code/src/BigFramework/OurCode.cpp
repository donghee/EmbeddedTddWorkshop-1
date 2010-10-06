//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * OurCode.cpp
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#include "OurCode.h"
#include "OurServiceRequests.h"

OurCode::OurCode(OurServiceRequests* server)
: server(server)
{
}

OurCode::~OurCode()
{
}

void OurCode::doMyThing()
{
    //do my thing, but get some help from the framework
    server->doSomething(this);
}

void OurCode::doSomethingIsDone()
{
    //finish doing my thing now that the result is back;
}
