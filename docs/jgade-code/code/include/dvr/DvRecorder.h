//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_DvRecorder_H
#define D_DvRecorder_H

///////////////////////////////////////////////////////////////////////////////
//
//  DvRecorder is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
//START: struct
typedef struct Program
{
    const char * name;
    int repeat;
    int channel;
    int startHour;
    int startMinute;
    int durationInMinutes;
    int priority;
    int preferences;
} Program;

enum {
    all_episodes, new_episodes, repeated_episodes,
    repeat, repeat_no,
    high_priority, medium_priority, low_priority
};

typedef struct
{
    int programCount;
    Program programs[100];
    //etc...
} DvRecorder;
//END: struct

//START: init
void DvrRecorder_Create();
void DvRecorder_RestorePrograms(DvRecorder*);
//END: init

void DvRecorder_Destroy();

#endif  // D_DvRecorder_H
