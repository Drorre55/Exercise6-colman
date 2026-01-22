#include "Survivor.h"
#include <string.h>

Survivor* CreateSurvivor(char* _name, float _age, int _followers) {
	char* nameCpy = malloc(strlen(_name) * sizeof *nameCpy);
	if (nameCpy == NULL) {
		printf("Problem with malloc");
		free(nameCpy);
		return NULL;
	}
	
	strcpy_s(nameCpy, sizeof(nameCpy), _name);
	
	Survivor survivor;
	survivor.age = _age;
	survivor.followers = _followers;
	survivor.name = nameCpy;
	
	Survivor* survivorPtr = &survivor;
	return survivorPtr;
}

Survivor* DuplicateSurvivor(Survivor* source) {
	Survivor* survivorCpy = malloc(sizeof(*source));
	if (survivorCpy == NULL) {
		printf("Problem with malloc");
		return NULL;
	}

	survivorCpy = CreateSurvivor(source->name, source->age, source->followers);
	return survivorCpy;
}