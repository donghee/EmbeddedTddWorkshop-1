//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material,
//- courses, books, articles, and the like. We make no guarantees
//- that this source code is fit for any purpose.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "unity_output_Spy.h"
#include <stdlib.h>
#include <string.h>

static int size;
static int count;
static char* buffer;

void UnityOutputCharSpy_Create(int s)
{
    size = s;
    count = 0;
    buffer = malloc(size);
    memset(buffer, 0, size);
}

void UnityOutputCharSpy_Destroy()
{
    size = 0;
    free(buffer);
}

int UnityOutputCharSpy_OutputChar(int c)
{
    if (count < (size-1))
        buffer[count++] = c;
    return c;
}

const char * UnityOutputCharSpy_Get()
{
    return buffer;
}

