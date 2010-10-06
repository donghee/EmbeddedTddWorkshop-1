//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/*
 * BigFramework.h
 *
 *  Created on: Sep 19, 2008
 *      Author: james
 */

#ifndef BIGFRAMEWORK_H_
#define BIGFRAMEWORK_H_
//include dependencies i don't want

class BigFrameworkClient;

class BigFramework
{
public:
    BigFramework();
    virtual ~BigFramework();

    static BigFramework* registerMe(BigFrameworkClient*);
    void doSomethingBig();

    void doSomethingIdontWantToUse();
    void etc();
    //plus many other dependencies i don't want

};

#endif /* BIGFRAMEWORK_H_ */
