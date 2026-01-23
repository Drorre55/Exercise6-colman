#include "Tribe.h"
#include <stdbool.h>
#include <stdio.h>


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
		for (int i = 0; i < t->num_of_survivors; i++) {
			Survivor* survivor = t->survivors[i];
			if (strcmp(survivor->name, s->name) == 0) {
				survivor->followers = s->followers;
				break;
			}
		}
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
	strcpy_s(tribeCpy->bandana_color, bandanaSize, source->bandana_color);
	
	size_t nameSize = strlen(source->name) + 1;
	char* tempName = malloc(nameSize);
	if (tempName == NULL) {
		printf("Problem with malloc. can't duplicate Tribe");
		free(tribeCpy);
		free(tempBandanaColor);
		return NULL;
	}
	tribeCpy->name = tempName;
	strcpy_s(tribeCpy->name, nameSize, source->name);

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
	return 0;
}

int UpdateFollowers(Tribe* t, char* name, int toAdd) {
	return 0;
}

int UpdateAge(Tribe* t, char* name, float newAge) {
	return 0;
}

int GetSurvivorFollowers(Tribe* t, char* name) {
	return 0;
}

void FreeTribe(Tribe* t) {

}
