#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "launch_data.h"
#include "functions.h"
#include "doom_functions.h"

char* allocateWadData(char *wad) {
	char *p = (char*) malloc(sizeof(char) * (strlen(wad) + 1));
	strcpy(p, wad);

	return p;
}

int isDataFile(char *wad) {
	if (endsWith(wad, ".wad") == 0 || endsWith(wad, ".pk3") == 0 || endsWith(wad, ".pk7") == 0) {
		return 0;
	}
	return 1;
}

int isValidIwad(char *wad) {
	FILE *fptr;	

	char *path = "iwad_list.txt";

	fptr = fopen(path, "r");

	if (fptr == NULL) {
		printf("Error reading file!!");
		return 2;
	}

	char lineBuffer[24];
	char lineArr[20][24];
	int charsToRead = 19;
	int lineCount = 0;

	const int MAXLINES = 20;

	while (fgets(lineBuffer, charsToRead, fptr)) {
		if (lineCount >= MAXLINES) {
			break;
		}

		strcpy(lineArr[lineCount], lineBuffer);
		lineCount++;
	}

	for (int i=0; i<lineCount; i++) {
		//check for a valid wad, in case of faliure remove
		//the file extension and try again...
		char *validWad = lineArr[i];


		//Remove the trailing \n, allowing for strcmp
		removeNewLine(validWad);

		if (strcmp(wad, validWad) == 0) {
			return 0;
		}

		removeExtension(validWad);

		if (strcmp(wad, validWad) == 0) {
			return 1;
		}
	}
	return 3;
}
/*
char* OldAddIWAD(char *wad, int retStatus) {
	if (retStatus == 2) {
		printf("ERROR reading iwad_list data!!");
		return NULL;
	}
	else if (retStatus == 1) {
		char *newPath = addExtension(".wad", wad);
		newPath = allocateWadData(newPath);
		return newPath;
	}
	else if (retStatus == 0) {
		return allocateWadData(wad);
	}

	return NULL;
}
*/
char* addIWAD(char *wad) {
	if (isDataFile(wad) == 0) {
		return allocateWadData(wad);
	}
	
	char *newPath = addExtension(".wad", wad);
	newPath = allocateWadData(newPath);
	return newPath;

}

char* handleCwad(char *wad) {
	return NULL;
}
