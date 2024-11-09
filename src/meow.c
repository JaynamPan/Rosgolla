#include <string.h>
#include <stdio.h>
#include "meow.h"

#define MEOW_LEN 4

static char getOpCode(const char *meowing){
	// 8 operate code are: > < + - . , [ ] 
	char result;
	if(strncmp(meowing, "Meow", MEOW_LEN) == 0){
		result = '>';
	}else if(strncmp(meowing, "meoW", MEOW_LEN) == 0){
		result = '<';
	}else if(strncmp(meowing, "mEow", MEOW_LEN) == 0){
		result = '+';
	}else if(strncmp(meowing, "meOw", MEOW_LEN) == 0){
		result = '-';
	}else if(strncmp(meowing, "meow", MEOW_LEN) == 0){
		result = '.';
	}else if(strncmp(meowing, "MEOW", MEOW_LEN) == 0){
		result = ',';
	}else if(strncmp(meowing, "MEow", MEOW_LEN) == 0){
		result = '[';
	}else if(strncmp(meowing, "meOW", MEOW_LEN) == 0){
		result = ']';
	}
	return result;
}

bool isMeowings(const char *source) {
	const char *meow = "meow";
	int meow_length = strlen(meow);

	// Pointer to iterate through the text without modifying it
	const char *ptr = source;

	while (*ptr) {
		// Skip spaces
		if (*ptr == ' ' || *ptr == '\r' || *ptr == '\n') {
			ptr++;
			continue;
		}
		// Check if the substring matches "meow" in any case
		if (strncasecmp(ptr, meow, MEOW_LEN) == 0) {
			ptr += meow_length; // Move past the "meow"
		} else {
			return false; // Found a non "meow" character
		}
	}
	return true; // All checks passed
}

void runMeow(const char *meowings) {
	char *parsedCode = parseMeow(meowings);
	runBrainFuck(parsedCode);
}

char* parseMeow(const char *meowings) {
	const char *meow = "meow";

	// Pointer to iterate through the text without modifying it
	const char *ptr = meowings;
	char *parsed = reallocate(NULL, 0, sizeof(char) * TAPE_SIZE);
	int count = 0;
	while (*ptr) {
		// Skip spaces
		if (*ptr == ' ' || *ptr == '\r' || *ptr == '\n') {
			ptr++;
			continue;
		}
		parsed[count] = getOpCode(ptr);
		ptr += MEOW_LEN;
		count++;
	}
	parsed[count] = '\0';
	return parsed;
}
