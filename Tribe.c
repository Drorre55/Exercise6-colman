#include "Tribe.h"

Tribe* AddSurvivor(Tribe* t, Survivor* s) {
	// if Tribe doesn't exist create it with default parameters
	if (t == NULL) {
		Tribe* tempTribe = malloc(sizeof(t));
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
			Survivor* survivor = *(t->survivors + i);
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
		*(t->survivors + t->num_of_survivors) = DuplicateSurvivor(s);
		t->num_of_survivors++;
	}

	return t;
}

Tribe* DuplicateTribe(Tribe* source) {
	return;
}

void SortByAge(Tribe* t) {

}

void SortByName(Tribe* t) {

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
