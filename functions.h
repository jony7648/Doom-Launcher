#ifndef FUNCTIONS.H
#define FUNCTIONS.H

extern int endsWith(char *string, char *suffix);
extern int reduceStrLen(int amount, char *string);
extern void removeExtension(char *string);
extern void removeNewLine(char *string);
extern char* addExtension(char *extension, char *oldString);
#endif
