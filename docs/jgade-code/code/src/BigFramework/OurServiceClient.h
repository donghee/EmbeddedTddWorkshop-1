//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * OurServiceClient.h
 *
 *  Created on: Sep 25, 2008
 *      Author: james
 */

#ifndef OurServiceCLIENT_H_
#define OurServiceCLIENT_H_

class OurServiceClient
{
public:
    OurServiceClient();
    virtual ~OurServiceClient();

    virtual void doSomethingIsDone() = 0;

};

#endif /* OurServiceCLIENT_H_ */
