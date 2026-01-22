#pragma once

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Survivor
{
	char* name;		//the name of the survivor
	float age;		//the age of the survivor
	int followers;	//how many followers he has on social networks
}Survivor;

Survivor* CreateSurvivor( char* _name, float _age, int _followers );
Survivor* DuplicateSurvivor( Survivor* source );
void FreeSurvivor( Survivor* s );