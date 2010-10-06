//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#include "IoPort.h"
#include <stdlib.h>
#include <memory.h>


void IoPort_Write_impl(IoPort* self,  uint16_t value) {
    //real code goes here
}

uint16_t IoPort_Read_impl(IoPort* self) {
    //real code goes here
    return 0xdead;
}

IoPort* IoPort_Create(uint16_t address, char* name) {
     IoPort* self = malloc(sizeof(IoPort));
     memset(self, 0, sizeof(IoPort));
     memcpy(self->name, name, sizeof(self->name));
     self->Write = IoPort_Write_impl;
     self->Read = IoPort_Read_impl;
     return self;
}

void IoPort_Destroy(IoPort* self) {
    free(self);
}

char* IoPort_GetName(IoPort* self) {
    return self->name;
}


