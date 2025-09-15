#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>
#include "launch_data.h"
#include "functions.h"
#include "doom_functions.h"

int searchForExtension(char *wad, char *fileName) {
	//fix weird seg fault when not adding file extension 

	FILE *fptr;

	char *path = "autocomplete_extensions.txt";
	
	fptr = fopen(path, "r");

	if (fptr == NULL) {
		printf("ERROR reading autocomplete_extensions file!!");
	}

	char lineBuffer[10];
	int charsToRead = 9;
	int maxExtensionLen = 10;
	lineBuffer[9] = '\0';

	int maxCompareLen = strlen(fileName) + maxExtensionLen + 1;
	int allocBytes = sizeof(char) * maxCompareLen;
	char *compareBuffer = (char*) malloc(allocBytes);


	while (fgets(lineBuffer, charsToRead, fptr)) {
		strcpy(compareBuffer, fileName);
		strcat(compareBuffer, lineBuffer);

		removeExtension(compareBuffer);

		if (strcmp(wad, compareBuffer) == 0) {
			return 0;
		}
	}

	free(compareBuffer);
	return 1;
}

void handleFrogottenExtensions(char* wad, LaunchData *data) {
	DIR *d;

	struct dirent *dir;

	d = opendir(".");

	if (dir == NULL) {
		printf("ERROR could not list file directory");
		return;
	}

	while ((dir = readdir(d)) != NULL) {
		char *fileName = dir->d_name;
	
		if (searchForExtension(wad, fileName) == 1) {
			continue;
		}


		if (isValidIwad(fileName) == 0) {
			data->iwadPath = addIWAD(fileName);
		}
		else if (isDataFile(fileName) == 0) {
			addPWAD(fileName, data);	
		}

		break;
	}

	closedir(d);
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
			skipCount--;
			continue;
		}

		char *arg = argv[i];
		char *nextArg = argv[i+1];

		if (i == argc - 1) {
			nextArg = NULL;
		}

		if (strcmp(arg, "-iwad") == 0) {
			launchData->iwadPath = addIWAD(nextArg);
			skipCount++;
			continue;
		}

		if (strcmp(arg, "-cwad") == 0) {
			launchData->cwadPath = addIWAD(nextArg);	
			skipCount++;
			continue;
		}

		//handle parameterless args
		if (isValidIwad(arg) == 0) {
			addIWAD(arg);
			launchData->iwadPath = allocateWadData(arg);
			continue;
		}

		if (isDataFile(arg) == 0 && bufferIndex < *pMaxWadCount) {
			strcpy(wadBuffer[bufferIndex], arg);
			bufferIndex++;	
		}

		handleFrogottenExtensions(arg, launchData);
	}

	//Do PWAD STUFF
	//fill launch data wad arr
	if (bufferIndex == 0) {
		return launchData;
	}


	allocateWadArray(bufferIndex, launchData);

	for (int i=0; i<bufferIndex; i++) {
		addPWAD(wadBuffer[i], launchData);
	}


	return launchData;
}

int main(int argc, char *argv[]) {
	LaunchData *launchData = parseCommandLine(argc, argv);
	for (int i=0; i<launchData->wadCount; i++) {
		printf("PWAD: %s\n", launchData->wadPathArr[i]);
	}

	printf("Iwad: %s\n", launchData->iwadPath);
	printf("CWAD: %s\n", launchData->cwadPath);


	return 0;
}
