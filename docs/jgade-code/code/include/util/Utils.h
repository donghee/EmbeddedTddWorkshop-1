//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net




#ifndef D_Utils_H
#define D_Utils_H
#if 0 //START: directCall
int FormatOutput(const char *, ...);
#endif //END: directCall

//START: indirectCall
extern int (*FormatOutput)(const char *, ...);
//END: indirectCall

#endif  // D_Utils_H
