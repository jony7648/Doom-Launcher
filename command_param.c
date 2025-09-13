#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "launch_data.h"
#include "functions.h"

int isDataFile(char *wad) {
	if (endsWith(wad, ".wad") == 0 || (endsWith(wad, ".pk3") == 0)) {
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
	return 2;
}

void handleIwad(char *wad, LaunchData *p) {
	int retStatus = isValidIwad(wad);

	if (retStatus > 1) {
		printf("ERROR reading iwad_list data!!");
		return;
	}
	else if (retStatus == 1) {
		p->iwadPath = addExtension(".wad", wad);
		return;
	}

	p->iwadPath = (char*) malloc(sizeof(char) * (strlen(wad) + 1));
	strcpy(p->iwadPath, wad);
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

		if (strcmp(arg, "-iwad") == 0) {
			handleIwad(nextArg, launchData);
			skipCount++;
			continue;
		}

		if (isDataFile(arg) == 0 && bufferIndex < *pMaxWadCount) {
			strcpy(wadBuffer[bufferIndex], arg);
			bufferIndex++;	
		}
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
		//printf("%s\n", launchData->wadPathArr[i]);
	}

	printf("Iwad: %s\n", launchData->iwadPath);

	return 0;
}
