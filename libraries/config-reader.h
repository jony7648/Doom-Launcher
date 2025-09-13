#ifndef CONFIG_READER_H
#define CONFIG_READER_H

typedef struct {
	char keyArr[500][50];
	char valueArr[500][50];
	int maxLines;
	int count;
} ParsedConfig;

extern ParsedConfig* parseConfig(char* path);
extern char* getConfigValue(char* key, ParsedConfig* cfgptr);

#endif
