//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net

//START: TEST_GROUP_RUNNER
#include "unity_fixture.h"

TEST_GROUP_RUNNER(sprintf)
{
    RUN_TEST_CASE(sprintf, NoFormatOperations);
    RUN_TEST_CASE(sprintf, InsertString);
    //END: TEST_GROUP_RUNNER
#if 0
    RUN_TEST_CASE(sprintf, StringWithSpace);
#endif
    //START: TEST_GROUP_RUNNER
}
//END: TEST_GROUP_RUNNER
