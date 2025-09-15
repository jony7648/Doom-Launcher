#ifndef DOOM_FUNCTIONS_H
#define DOOM_FUNCTIONS_H

extern int isDataFile(char *wad);
extern int isValidIwad(char *wad);
extern char* allocateWadData(char *wad);
extern char* addIWAD(char *wad);
extern char* handleCwad(char *wad);
#endif



