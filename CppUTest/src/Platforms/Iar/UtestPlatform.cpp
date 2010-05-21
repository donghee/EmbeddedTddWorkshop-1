/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <math.h>
#include "CppUTest/TestHarness.h"
#undef malloc
#undef calloc
#undef realloc
#undef free
#include "CppUTest/TestRegistry.h"
#include "CppUTest/PlatformSpecificFunctions.h"

static jmp_buf test_exit_jmp_buf[10];
static int jmp_buf_index = 0;

bool Utest::executePlatformSpecificSetup()
{
   if (0 == setjmp(test_exit_jmp_buf[jmp_buf_index])) {
      jmp_buf_index++;
      setup();
      jmp_buf_index--;
      return true;
   }
   return false;
}

void Utest::executePlatformSpecificTestBody()
{
   if (0 == setjmp(test_exit_jmp_buf[jmp_buf_index])) {
      jmp_buf_index++;
      testBody();
      jmp_buf_index--;
   }
}

void Utest::executePlatformSpecificTeardown()
{
   if (0 == setjmp(test_exit_jmp_buf[jmp_buf_index])) {
      jmp_buf_index++;
      teardown();
      jmp_buf_index--;
   }
}

void Utest::executePlatformSpecificRunOneTest(TestPlugin* plugin, TestResult& result)
{
    if (0 == setjmp(test_exit_jmp_buf[jmp_buf_index])) {
       jmp_buf_index++;
       runOneTest(plugin, result);
       jmp_buf_index--;
    }
}

void Utest::executePlatformSpecificExitCurrentTest()
{
   jmp_buf_index--;
   longjmp(test_exit_jmp_buf[jmp_buf_index], 1);
}

///////////// Time in millis

static long TimeInMillisImplementation()
{
   clock_t t = clock();

   t = t * 10;

   return  1;
}

static long (*timeInMillisFp) () = TimeInMillisImplementation;

long GetPlatformSpecificTimeInMillis()
{
	return timeInMillisFp();
}

void SetPlatformSpecificTimeInMillisMethod(long (*platformSpecific) ())
{
	timeInMillisFp = (platformSpecific == 0) ? TimeInMillisImplementation : platformSpecific;
}

///////////// Time in String

static const char* TimeStringImplementation()
{
	time_t tm = time(NULL);
	return ctime(&tm);
}

static const char* (*timeStringFp) () = TimeStringImplementation;

const char* GetPlatformSpecificTimeString()
{
	return timeStringFp();
}

void SetPlatformSpecificTimeStringMethod(const char* (*platformMethod) ())
{
	timeStringFp = (platformMethod == 0) ? TimeStringImplementation : platformMethod;
}

int PlatformSpecificAtoI(const char*str)
{
   return atoi(str);
}

int PlatformSpecificStrLen(const char* str)
{
   return strlen(str);
}

char* PlatformSpecificStrCat(char* s1, const char* s2)
{
   return strcat(s1, s2);
}

char* PlatformSpecificStrCpy(char* s1, const char* s2)
{
   return strcpy(s1, s2);
}

char* PlatformSpecificStrNCpy(char* s1, const char* s2, unsigned int size)
{
   return strncpy(s1, s2, size);
}

int PlatformSpecificStrCmp(const char* s1, const char* s2)
{
   return strcmp(s1, s2);
}

int PlatformSpecificStrNCmp(const char* s1, const char* s2, unsigned int size)
{
   return strncmp(s1, s2, size);
}

char* PlatformSpecificStrStr(const char* s1, const char* s2)
{
   return strstr((char*)s1, (char*)s2);
}

int PlatformSpecificVSNprintf(char *str, unsigned int size, const char* format, va_list args)
{
   return vsnprintf( str, size, format, args);
}

PlatformSpecificFile PlatformSpecificFOpen(const char* filename, const char* flag)
{
   return 0;
}

void PlatformSpecificFPuts(const char* str, PlatformSpecificFile file)
{
}

void PlatformSpecificFClose(PlatformSpecificFile file)
{
}

void PlatformSpecificFlush()
{
}

int PlatformSpecificPutchar(int c)
{
  return putchar(c);
}

void* PlatformSpecificMalloc(unsigned int size)
{
   return malloc(size);
}

void* PlatformSpecificRealloc (void* memory, unsigned int size)
{
   return realloc(memory, size);
}

void PlatformSpecificFree(void* memory)
{
   free(memory);
}

void* PlatformSpecificMemCpy(void* s1, const void* s2, unsigned int size)
{
   return memcpy(s1, s2, size);
}

int PlatformSpecificAtExit(void (*func) ())
{
   return atexit(func);
}

double PlatformSpecificFabs(double d)
{
   return fabs(d);
}

