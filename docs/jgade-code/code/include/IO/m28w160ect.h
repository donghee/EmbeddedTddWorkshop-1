//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_m28w160ect_H
#define D_m28w160ect_H

typedef enum
{
	ProgramCommand = 0x40,
	Reset = 0xff
} Flash_Command;

typedef enum
{
	ReadyBit = 1<<7,
	EraseSuspendBit = 1<<6,
	EraseErrorBit = 1<<5,
	ProgramErrorBit = 1<<4,
	VppErrorBit = 1<<3,
	ProgramSuspendBit = 1<<2,
	BlockProtectionErrorBit = 1<<1,
	ReservedBit = 1
} StatusRegisterBits;

typedef enum
{
	CommandRegister = 0x0,
	StatusRegister = 0x0
} Flash_Registers;


#endif //D_m28w160ect_H
