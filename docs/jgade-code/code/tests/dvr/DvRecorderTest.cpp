//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "CppUTest/TestHarness.h"

extern "C"
{
#include "DvRecorder.h"
#include <memory.h>
}

//START: firstSetup
static DvRecorder recorderData = {
    4,
    {
        {"Rocky and Bullwinkle", repeat, 2, 8, 30, 30, high_priority, all_episodes},
        {"Bugs Bunny", repeat, 9, 8, 30, 30, high_priority, all_episodes},
        {"Dr. Who", repeat, 11, 23, 0, 90, high_priority, repeated_episodes},
        {"Law and Order", repeat, 5, 21, 0, 60, high_priority, all_episodes},
        { 0 }
    }
};
//END: firstSetup

#if 0 //START: firstSetup
TEST_GROUP(DvRecorder)
{
    DvRecorder recorder;
    void setup()
    {
        memcpy(&recorder, &recorderData, sizeof(recorder));
        DvrRecorder_Create();
        DvRecorder_RestorePrograms(&recorder);
    }
    
    void teardown()
    {
       DvRecorder_Destroy();
    }
};
//END: firstSetup
#endif

//START: twoStageSetup
TEST_GROUP(DvRecorder)
{
    DvRecorder recorder;
    void setup()
    {
        memcpy(&recorder, &recorderData, sizeof(recorder));
        DvrRecorder_Create();
    }

    void teardown()
    {
       DvRecorder_Destroy();
    }
};

TEST(DvRecorder, RestoreSomePrograms)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}
//END: twoStageSetup


//START: overridesDefaultData
TEST(DvRecorder, RestoreNoPrograms)
{
    recorder.programCount = 0;
    recorder.programs[0].name = 0;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

TEST(DvRecorder, RecordWithRepeat)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

TEST(DvRecorder, RecordWithNoRepeat)
{
    recorder.programs[0].repeat = repeat_no;
    recorder.programs[1].repeat = repeat_no;
    recorder.programs[2].repeat = repeat_no;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

TEST(DvRecorder, RecordConflictFirstHighPriorityWins)
{
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

TEST(DvRecorder, RecordConflictHighPriorityWins)
{
    recorder.programs[0].priority = low_priority;
    DvRecorder_RestorePrograms(&recorder);
    //etc...
}

//END: overridesDefaultData


