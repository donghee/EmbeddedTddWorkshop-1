//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "DvRecorder.h"
#include <stdlib.h>
#include <memory.h>

void DvrRecorder_Create()
{

}

void DvRecorder_RestorePrograms(DvRecorder * programs)
{
}

void DvRecorder_Destroy()
{
}

#if 0
#include <pthread.h>

void DvRecorder_startScheduledPrograms()
{
    ScheduledProgram p;
    File dest;
    
    boss_mutex_lock(ScheduledProgram_mutex);
    p = DvRecorder_getNextScheduledProgram();
    while (p)
    {       
        if (ScheduledProgram_isTimeToStart(p)) {
            if (dvr->isSleeping) {
                boss_mutex_lock(audioOut->mutex);
                audioOut->muted = TRUE;
                turnOffAudio(audioOut->port);
                boss_mutex_lock(dvr->mutex);
                if (dvr->activeRecordingsCount 
                        >= MAX_SIMULTANEOUS_RECORDINGS) {
                    boss_mutex_unlock(ScheduledProgram_mutex);
                    boss_mutex_unlock(dvr->mutex);
                    return;
                }
                dest = openRecordingFile(p);
                dvr->activeRecordingsCount++;
                record(dest, p->channel);
                boss_mutex_lock(audioOut->mutex);
                boss_mutex_lock(dvr->mutex);    
            } 
            // ...more of the same...
        }
        p = DvRecorder_getNextScheduledProgram(p);
     }    
    boss_mutex_unlock(ScheduledProgram_mutex);
}

void DvRecorder_startScheduledPrograms()
{
    ScheduledProgram p;
    
    Acquire_ProgramSchedule_locks();
    p = DvRecorder_getFirstScheduledProgram();

    while (p && ! recordingLimitReached())
    { 
        ScheduledProgram_startReadyProgram(p);
        p = DvRecorder_getNextScheduledProgram(p);
    }    
    Release_ProgramSchedule_locks();
}
#endif