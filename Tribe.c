#define _CRT_SECURE_NO_WARNINGS
#include "Tribe.h"
#include <stdbool.h>
#include <stdio.h>


Survivor* GetSurvivorByName(Tribe* t, char* name)
{
	for (int i = 0; i < t->num_of_survivors; i++) {
		Survivor* survivor = t->survivors[i];
		if (strcmp(survivor->name, name) == 0) {
			return survivor;
		}
	}
	return NULL;
}

Tribe* AddSurvivor(Tribe* t, Survivor* s) {
	// if Tribe doesn't exist create it with default parameters
	if (t == NULL) {
		Tribe* tempTribe = malloc(sizeof *tempTribe);
		if (tempTribe == NULL) {
			printf("Problem with malloc. Couldn't create Tribe");
			return NULL;
		}

		t = tempTribe;
		t->bandana_color = "Red";
		t->name = "Colman";
		Survivor* survivors[1] = { DuplicateSurvivor(s) };
		t->survivors = survivors;
		t->num_of_survivors = 1;
	}
	// Check if s->name already equals one of t->survivors name and update it's followers
	else if (t->survivors) {
		Survivor* survivor = GetSurvivorByName(t, s->name);
		if (survivor != NULL) survivor->followers = s->followers;
	}
	// Add Survivor to Tribe
	else {
		Survivor** tempSurvivorsPtr = realloc(t->survivors, (t->num_of_survivors + 1) * sizeof * tempSurvivorsPtr);
		if (tempSurvivorsPtr == NULL) {
			printf("Problem with realloc. Couldn't add survivor");
			return NULL;
		}

		t->survivors = tempSurvivorsPtr;
		t->survivors[t->num_of_survivors] = DuplicateSurvivor(s);
		t->num_of_survivors++;
	}

	return t;
}

Tribe* DuplicateTribe(Tribe* source) {
	Tribe* tribeCpy = malloc(sizeof *tribeCpy);
	if (tribeCpy == NULL) {
		printf("Problem with malloc. can't duplicate Tribe");
		return NULL;
	}

	size_t bandanaSize = strlen(source->bandana_color) + 1;
	char* tempBandanaColor = malloc(bandanaSize);
	if (tempBandanaColor == NULL) {
		printf("Problem with malloc. can't duplicate Tribe");
		free(tribeCpy);
		return NULL;
	}
	tribeCpy->bandana_color = tempBandanaColor;
	strcpy(tribeCpy->bandana_color, source->bandana_color);
	
	size_t nameSize = strlen(source->name) + 1;
	char* tempName = malloc(nameSize);
	if (tempName == NULL) {
		printf("Problem with malloc. can't duplicate Tribe");
		free(tribeCpy);
		free(tempBandanaColor);
		return NULL;
	}
	tribeCpy->name = tempName;
	strcpy(tribeCpy->name, source->name);

	tribeCpy->num_of_survivors = source->num_of_survivors;

	Survivor** tempSurvivors = malloc(source->num_of_survivors * sizeof * tempSurvivors);
	if (tempSurvivors == NULL) {
		printf("Problem with malloc. can't duplicate Tribe");
		free(tribeCpy);
		free(tempBandanaColor);
		free(tempName);
		return NULL;
	}
	tribeCpy->survivors = tempSurvivors;
	for (int i = 0; i < source->num_of_survivors; i++) {
		tribeCpy->survivors[i] = DuplicateSurvivor(source->survivors[i]);
	}

	return tribeCpy;
}

void MoveSurvivorFromEndToStartSlice(Survivor* survivors[], int start, int end, bool includeEdge) {
	Survivor* survivorToMove = survivors[end];

	start = includeEdge ? start - 1 : start;
	for (int q = end - 1; q > start; q--) {
		survivors[q + 1] = survivors[q];
	}
	// put current survivor in the start of the slice
	survivors[start + 1] = survivorToMove;
}


void SortByAge(Tribe* t) {
	for (int i = 1; i < t->num_of_survivors; i++) {
		Survivor* currentSurvivor = t->survivors[i];

		// iterate over the numbers to the left of current number, from closest to the farthest one
		// put the current number in the appropriate index on the left with respect to the slice from 0 to current
		// and push all the relavent numbers to the right
		for (int j = i - 1; j >= 0; j--) {
			Survivor* previousSurvivor = t->survivors[j];

			if (currentSurvivor->age > previousSurvivor->age) {
				MoveSurvivorFromEndToStartSlice(t->survivors, j, i, false);
				break;
			}
			else if (j == 0) {
				MoveSurvivorFromEndToStartSlice(t->survivors, j, i, true);
			}
		}
	}
}

void SortByName(Tribe* t) {
	for (int i = 1; i < t->num_of_survivors; i++) {
		Survivor* currentSurvivor = t->survivors[i];

		// iterate over the numbers to the left of current number, from closest to the farthest one
		// put the current number in the appropriate index on the left with respect to the slice from 0 to current
		// and push all the relavent numbers to the right
		for (int j = i - 1; j >= 0; j--) {
			Survivor* previousSurvivor = t->survivors[j];

			if (strcmp(currentSurvivor->name, previousSurvivor->name) > 0) {
				MoveSurvivorFromEndToStartSlice(t->survivors, j, i, false);
				break;
			}
			else if (j == 0) {
				MoveSurvivorFromEndToStartSlice(t->survivors, j, i, true);
			}
		}
	}
}

int TotalFollowers(Tribe* t) {
	int sumFollowers = 0;
	for (int i = 0; i < t->num_of_survivors; i++) {
		sumFollowers += t->survivors[i]->followers;
	}
	return sumFollowers;
}

int UpdateFollowers(Tribe* t, char* name, int toAdd) {
	Survivor* survivor = GetSurvivorByName(t, name);
	if (survivor != NULL) {
		survivor->followers += toAdd;
		return 1;
	}
	return 0;
}

int UpdateAge(Tribe* t, char* name, float newAge) {
	Survivor* survivor = GetSurvivorByName(t, name);
	if (survivor != NULL) {
		survivor->age = newAge;
		return 1;
	}
	return 0;
}

int GetSurvivorFollowers(Tribe* t, char* name) {
	Survivor* survivor = GetSurvivorByName(t, name);
	if (survivor != NULL) {
		return survivor->followers;
	}
	return -1;
}

void FreeTribe(Tribe* t) {
	for (int i = 0; i < t->num_of_survivors; i++) {
		FreeSurvivor(t->survivors[i]);
		t->survivors[i] = NULL;
	}
	t->survivors = NULL;
	free(t->name);
	t->name = NULL;
	free(t->bandana_color);
	t->bandana_color = NULL;
	free(t);
	t = NULL;
}
