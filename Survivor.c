#include "Survivor.h"
#include <string.h>
#include <stdio.h>

Survivor* CreateSurvivor(char* _name, float _age, int _followers) {
	size_t nameSize = strlen(_name) + 1;
	char* nameCpy = malloc(nameSize);
	if (nameCpy == NULL) {
		printf("Problem with malloc");
		return NULL;
	}
	
	strcpy_s(nameCpy, nameSize, _name);
	
	Survivor* survivorPtr = malloc(sizeof *survivorPtr);
	if (survivorPtr == NULL) {
		printf("Problem with malloc");
		free(nameCpy);
		return NULL;
	}

	survivorPtr->age = _age;
	survivorPtr->followers = _followers;
	survivorPtr->name = nameCpy;
	
	return survivorPtr;
}

Survivor* DuplicateSurvivor(Survivor* source) {
	return CreateSurvivor(source->name, source->age, source->followers);
}

void FreeSurvivor(Survivor* s) {
	free(s->name);
	free(s);
}