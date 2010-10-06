//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * BFwAdaptor.h
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#ifndef BFWADAPTOR_H_
#define BFWADAPTOR_H_

#include "BigFramework.h"
#include "BigFrameworkClient.h"
#include "OurServiceRequests.h"

class OurServiceClient;

class BFwAdaptor : public OurServiceRequests
                 , private BigFrameworkClient
{
public:
    BFwAdaptor();
    virtual ~BFwAdaptor();

    virtual void yourRequestIsDone(int result);
    void doSomething(OurServiceClient*);

private:
    OurServiceClient* client;
    BigFramework* server;
};

#endif /* BFWADAPTOR_H_ */
