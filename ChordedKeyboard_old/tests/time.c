#ifdef __AVR__
  #include "../../ArduinoCore/WProgram.h"
  void (*my_delay)(unsigned long) = delay;
  unsigned long (*my_millis)(void) = millis;
#else
  void (*my_delay)(unsigned long);
  unsigned long (*my_millis)(void);
#endif
                          


