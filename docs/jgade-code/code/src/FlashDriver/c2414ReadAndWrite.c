//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


/***************** STFL-I Flash Memory Driver- Read and Write*********************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c2414FlashReadAndWrite.h"      /* Header file with global prototypes */



/*******************************************************************************
Function:     uCPUBusType FlashRead( udword udAddrOff )
Arguments:    udAddrOff is the offset into the flash to read from.
Return values:The uCPUBusType content at the address offset.
Description:  This function is used to read a uCPUBusType from the flash.
   On many microprocessor systems a macro can be used instead, increasing the
   speed of the flash routines. For example:

   #define FlashRead( udAddrOff ) ( BASE_ADDR[udAddrOff] )

   A function is used here instead to allow the user to expand it if necessary.

Pseudo Code:
   Step 1: Return the value at double-word offset udAddrOff
*******************************************************************************/
uCPUBusType FlashRead( udword udAddrOff ) {
   /* Step 1: Return the value at double-word offset udAddrOff */
   return BASE_ADDR[udAddrOff];
} /* EndFunction FlashRead */



/*******************************************************************************
Function:     void FlashWrite( udword udAddrOff, uCPUBusType ucVal )
Arguments:    udAddrOff is double-word offset in the flash to write to.
   ucVal is the value to be written
Return Value: None
Description: This function is used to write a uCPUBusType to the flash.
*******************************************************************************/
void FlashWrite( udword udAddrOff, uCPUBusType ucVal ) {
   /* Write ucVal to the double-word offset in flash */
   BASE_ADDR[udAddrOff] = ucVal;
} /* EndFunction FlashWrite */

