//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "OurPrintfSpy.h"
#include <stdio.h>
#include <stdarg.h>

static char* buffer_ptr;
static int buffer_size = 0;
static int buffer_offset = 0;
static int buffer_used = 0;

#define WINDOWS_VSNPRINTF_OVERWRITE -1

int OurPrintf_spy(const char* format, ...)
{
    int written_size;
    va_list arguments;
    va_start(arguments, format);
    written_size = vsnprintf(buffer_ptr + buffer_offset, buffer_size - buffer_used, format, arguments);
    if (written_size == WINDOWS_VSNPRINTF_OVERWRITE)
    {
        written_size = buffer_size - buffer_used;
        buffer_ptr[buffer_offset + written_size - 1] = 0;
    }

    buffer_offset += written_size;
    buffer_used += written_size;
    va_end(arguments);
    return 1;
}

void OurPrintf_spy_setBuffer(char* buffer, int size)
{
    buffer_ptr = buffer;
    buffer_size = size;
    buffer_offset = 0;
    buffer_used = 0;
    buffer[0] = '\0';
}
