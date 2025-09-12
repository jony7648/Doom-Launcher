#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "launch_data.h"

LaunchData* newLaunchData() {
	LaunchData *launchData = malloc(sizeof(LaunchData));

	launchData->maxWadCount = 10;
	launchData->wadCount = 0;
	launchData->maxWadLen = 20;

	

	return launchData;
}

void allocateWadArray(int count, LaunchData *p) {
	size_t allocAmount = sizeof(char*) * count;
	p->wadPathArr = (char**) malloc(allocAmount);
	//p->stringValues = (char**) malloc(sizeof(char) * maxKeyLength * count);
}


int addPWAD(char* wadPath, LaunchData *launchData) {
	//malloc the new string data to work with the struct

	int *pWadCount = &launchData->wadCount;
	int maxWadCount = launchData->maxWadCount;
	int maxWadLen = launchData->maxWadLen;
	char **wadPathArr = launchData->wadPathArr;
	size_t wadPathLen = strlen(wadPath) + 1;

	if (*pWadCount > maxWadCount) {
		return 1;
	}
	else if (wadPathLen > maxWadLen) {
		return 1;
	}

	//strcpy(wadPathArr[*pWadCount], wadPath);
	int allocAmount = sizeof(char) * (strlen(wadPath) + 1);

	wadPathArr[*pWadCount] = (char**) malloc(allocAmount);
	wadPathArr[*pWadCount][0] = '\0';
	strcpy(launchData->wadPathArr[*pWadCount], wadPath);
	*pWadCount += 1;

	return 0;		
}
