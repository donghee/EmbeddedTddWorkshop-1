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

//START: interface
typedef struct LightDriver LightDriver;

void LightDriver_Destroy(LightDriver*);
void LightDriver_TurnOn(LightDriver*);
void LightDriver_TurnOff(LightDriver*);
const char * LightDriver_GetType(LightDriver*);
int LightDriver_GetId(LightDriver*);

typedef void LightDriverFunction(LightDriver*);

LightDriver* LightDriver_Create(LightDriver* self,
                                const char * type,
                                int id,
                                LightDriverFunction* destroy,
                                LightDriverFunction* on,
                                LightDriverFunction* off);

//END: interface

LightDriver* LightDriver_CreateNull(int id);

//START: struct
struct LightDriver
{
    const char* type;
    int id;
    LightDriverFunction* destroy;
    LightDriverFunction* on;
    LightDriverFunction* off;
};
//END: struct

#if 0 //START: structWithComment
//Private: do not access members of this structure.
struct LightDriver
{
    const char* type;
    int id;
    LightDriverFunction* destroy;
    LightDriverFunction* on;
    LightDriverFunction* off;
};
//END: structWithComment
#endif

#endif  // D_LightDriver_H
