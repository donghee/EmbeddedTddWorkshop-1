//- Copyright (c) 2010 James Grenning --- All rights reserved
//- You may use the source code in your own projects, however
//- the source code may not be used to create training material, 
//- courses, books, articles, and the like. We make no guarantees 
//- that this source code is fit for any purpose. 
//- www.renaissancesoftware.net james@renaissancesoftware.net


#ifndef D_LightSwitch_H
#define D_LightSwitch_H

typedef struct LightSwitch LightSwitch;

struct LightSwitch
{
	void (*TurnOn)(LightSwitch*);
	void (*TurnOff)(LightSwitch*);
	void (*Brighter)(LightSwitch*);
	void (*Darker)(LightSwitch*);
	char* name;
	int id;
};

void LightSwitch_TurnOn(LightSwitch*);
void LightSwitch_TurnOff(LightSwitch*);


//LightSwitch* LightSwitch_Create(char* model, char* name, int id);
//void initAndTurnOn()
//{
//	LightSwitch* ls;
//	ls = LightSwitch_Create("M74", "Front Door", 17);
//	LightSwitch_TurnOn(ls);
//}

#endif // D_LightSwitch_H
