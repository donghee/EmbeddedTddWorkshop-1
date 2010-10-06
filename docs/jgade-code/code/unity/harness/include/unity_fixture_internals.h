/*
 * unity_fixture.h
 *
 *  Created on: Apr 15, 2010
 *      Author: james
 */

#ifndef UNITY_FIXTURE_INTERNALS_H_
#define UNITY_FIXTURE_INTERNALS_H_

typedef void unityfunction();
void UnityTestRunner(unityfunction * setup,
        unityfunction * body,
        unityfunction * teardown,
        const char * printableName,
        const char * group,
        const char * name,
        const char * file, int line);

void UnityMalloc_StartTest();
void UnityMalloc_EndTest();
int UnityFailureCount();
int UnityGetCommandLineOptions(int argc, const char* argv[]);
void UnityConcludeFixtureTest();

void UnityPointer_Set(void ** ptr, void * newValue);
void UnityPointer_UndoAllSets();
void UnityPointer_Init();

void UnityAssertEqualPointer(const void * expected,
                            const void * actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber);

#endif /* UNITY_FIXTURE_INTERNALS_H_ */
