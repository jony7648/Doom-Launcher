#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "launch_data.h"

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

	if (strcmp(compareString, suffix) == 0) {
		retValue = 0;
	}

	free(compareString);

	return retValue;
}

int isDataFile(char *wad) {
	if (endsWith(wad, ".wad") == 0 || (endsWith(wad, ".pk3") == 0)) {
		return 0;
	}

	return 1;
}


void handleIwad(char *wad, LaunchData *p) {
	if (isDataFile(wad) != 0) {
		printf("This is not a valid data file!");
		return;

	
	p->iwadPath = (char*) malloc(sizeof(char) * (strlen(wad) + 1));
	strcpy(p->iwadPath, wad);
	}
}

LaunchData* parseCommandLine(int argc, char **argv) {
	LaunchData *launchData = newLaunchData();

	int argvStartIndex = 1;

	int *pWadCount = &launchData->wadCount;
	int *pMaxWadCount = &launchData->maxWadCount;
	int maxWadLen = launchData->maxWadLen;

	char wadBuffer[20][20];
	int bufferIndex = 0;

	int skipCount = 0;

	for (int i=1; i<argc; i++) {
		if (skipCount > 0) {
			continue;
		}

		char *arg = argv[i];
		char *nextArg = argv[i+1];

		if (strcmp(arg, "-iwad") == 0) {
			handleIwad(nextArg, launchData);
			skipCount++;
			continue;
		}

		if (endsWith(argv[i], ".wad") == 0 && *pWadCount < *pMaxWadCount) {
			strcpy(wadBuffer[bufferIndex], arg);
			bufferIndex++;	
		}
	}

	//fill launch data wad arr
	if (bufferIndex > 0) {
		allocateWadArray(bufferIndex, launchData);
		//add a max wad file len for the struct
	}


	for (int i=0; i<bufferIndex; i++) {
		addPWAD(wadBuffer[i], launchData);
	}
	
	// Try to make malloc work


	return launchData;
}

int main(int argc, char *argv[]) {
	LaunchData *launchData = parseCommandLine(argc, argv);
/*
	for (int i=0; i<launchData->wadCount; i++) {
		printf("yes");
	}

	*/
	return 0;
}
