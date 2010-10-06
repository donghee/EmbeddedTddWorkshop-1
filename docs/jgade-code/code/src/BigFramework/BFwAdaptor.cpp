//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * BFwAdaptor.cpp
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#include "BFwAdaptor.h"
#include "BigFramework.h"
#include "OurServiceClient.h"

BFwAdaptor::BFwAdaptor()
{
    server = BigFramework::registerMe(this);
}

BFwAdaptor::~BFwAdaptor()
{
}

void BFwAdaptor::yourRequestIsDone(int result)
{
    //a real adaptor might have to do some parameter
    //translation to call the BigFramework.
    client->doSomethingIsDone();
}

void BFwAdaptor::doSomething(OurServiceClient* client)
{
    //a real adaptor might have to do some parameter
    //translation on the way back too.
    this->client = client;
    server->doSomethingBig();
}
