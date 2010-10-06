//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "FormatOutputSpy.h"
#include <stdio.h>
#define WINDOWS_VSNPRINTF_OVERWRITE -1
#if 0 //put this after vsnprintf for windows
    if (written_size == WINDOWS_VSNPRINTF_OVERWRITE)
    {
        written_size = buffer_size - buffer_used;
        buffer[buffer_offset + written_size - 1] = 0;
    }
#endif

//START: source
#include <stdlib.h>
#include <stdarg.h>

static char * buffer = 0;
static size_t buffer_size = 0;
static int buffer_offset = 0;
static int buffer_used = 0;


void FormatOutputSpy_Create(int size)
{
    FormatOutputSpy_Destroy();
    buffer_size = size+1;
    buffer = (char *)malloc(buffer_size);
    buffer_offset = 0;
    buffer_used = 0;
    buffer[0] = '\0';
}

void FormatOutputSpy_Destroy()
{
    if (buffer == 0)
        return;

    free(buffer);
    buffer = 0;
}

int FormatOutputSpy(const char * format, ...)
{
    int written_size;

    va_list arguments;
    va_start(arguments, format);
    written_size = vsnprintf(buffer + buffer_offset,
                buffer_size - buffer_used, format, arguments);
    buffer_offset += written_size;
    buffer_used += written_size;
    va_end(arguments);
    return 1;
}

const char * FormatOutputSpy_GetOutput()
{
    return buffer;
}
//END: source
