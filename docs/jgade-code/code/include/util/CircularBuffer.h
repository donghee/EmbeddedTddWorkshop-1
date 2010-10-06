//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net



//START: interface
#ifndef D_CircularBuffer_H
#define D_CircularBuffer_H

typedef struct CircularBuffer CircularBuffer;

CircularBuffer * CircularBuffer_Create(int capacity);
void CircularBuffer_Destroy(CircularBuffer *);
int CircularBuffer_IsEmpty(CircularBuffer *);
int CircularBuffer_IsFull(CircularBuffer *);
int CircularBuffer_Put(CircularBuffer *, int);
int CircularBuffer_Get(CircularBuffer *);
int CircularBuffer_Capacity(CircularBuffer *);
void CircularBuffer_Print(CircularBuffer *);
//END: interface
int CircularBuffer_VerifyIntegrity(CircularBuffer *);
//START: interface
#endif  // D_CircularBuffer_H
//END: interface
