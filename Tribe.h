#pragma once

#include "Survivor.h"

typedef struct Tribe
{
	Survivor** survivors;	//a pointer to an array of pointers to survivors
	int num_of_survivors;	//the number of survivors in the tribe
	char* name;				//the name of the tribe
	char* bandana_color;	//the color of the tribe's bandana
} Tribe;

Tribe* AddSurvivor( Tribe* t, Survivor* s );
Tribe* DuplicateTribe( Tribe* source );
void SortByAge( Tribe* t );
void SortByName( Tribe * t );
int TotalFollowers( Tribe* t );
int UpdateFollowers( Tribe * t, char* name, int toAdd );
int UpdateAge( Tribe * t, char* name, float newAge );
int GetSurvivorFollowers( Tribe* t, char* name );
void FreeTribe( Tribe* t );