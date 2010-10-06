//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * BigFrameworkClient.h
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#ifndef BIGFRAMEWORKCLIENT_H_
#define BIGFRAMEWORKCLIENT_H_

class BigFrameworkClient
{
public:
    BigFrameworkClient();
    virtual ~BigFrameworkClient();

    virtual void yourRequestIsDone(int result)
    { /* default impl */ }

private:
    //dependencies to BigFramework internals

};

#endif /* BIGFRAMEWORKCLIENT_H_ */
