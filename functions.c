#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

int endsWith(char *string, char *suffix) {
	if (strlen(string) < strlen(suffix)) {
		return 2;
	}

	int retValue = 1;

	int allocAmount = sizeof(char) * (strlen(suffix) + 1);
	char *compareString = malloc(allocAmount);

	size_t startIndex = strlen(string) - strlen(suffix);
	int stringIndex = 0;
	

	for (int i=startIndex; i<strlen(string); i++) {
		compareString[stringIndex] = string[i];
		stringIndex++;
	}


	//printf("Compare: %s\nSUFFIX: %s\n", compareString, suffix);

	if (strcmp(compareString, suffix) == 0) {
		retValue = 0;
	}

	free(compareString);

	return retValue;
}

int reduceStrLen(int amount, char *string) {
	int endIndex = strlen(string);

	if (endIndex > amount) {
		int index = endIndex - amount - 1;
		string[index] = '\0';
		return 0;
	} 

	return 1;
}

void removeExtension(char *string) {
	size_t startIndex = strlen(string) - 1;

	for (int i=startIndex; i>0; i--) {
		if (string[i] == '.') {
			string[i] = '\0';	
		}
	}
}

char* addExtension(char *extension, char *oldString) {
	int allocAmonut = sizeof(char) * (strlen(oldString) + strlen(extension) + 1);	
	char *p = (char*) malloc(allocAmonut);
	p[0] = '\0';

	strcpy(p, oldString);
	strcat(p, extension);

	return p;
}

void removeNewLine(char *string) {
	int index = strlen(string) - 1;

	if (string[index] == '\n') {
		string[index] = '\0';
	}
}
