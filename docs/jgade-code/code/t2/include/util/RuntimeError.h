//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_RuntimeError_H
#define D_RuntimeError_H

void RuntimeError(char * description, int parameter, char * file, int line);

#define RUNTIME_ERROR(description, parameter) RuntimeError(description, parameter, __FILE__, __LINE__)

#endif
