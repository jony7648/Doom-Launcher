#ifndef LAUNCH_DATA_H
#define LAUNCH_DATA_H

typedef struct {
	char *sourcePort;
	char *sourcePortPath;
	char *iwadPath;
	char *cwadPath;
	//char wadPathArr[100][100];
	char **wadPathArr;
	int wadCount;
	int maxWadCount;
	int maxWadLen;
	char *recordDemoPath;
	char *playDemoPath;
	int noMonsters;
	int mapToWarp;
} LaunchData;


extern LaunchData* newLaunchData();
extern int addPWAD(char *wadPath, LaunchData *launchData);
extern void allocateWadArray(int count, LaunchData *launchData);

#endif
