//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightDriver_H
#define D_LightDriver_H

///////////////////////////////////////////////////////////////////////////////
//
//  LightDriver is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

//START: common
typedef struct LightDriver LightDriver;
typedef enum  LightDriverType {
    TestLightDriver,
    X10,
    AcmeWireless,
    MemoryMapped
 } LightDriverType;

struct LightDriver
{
    LightDriverType type;
    int id;
};
//END: common


#endif  // D_LightDriver_H
