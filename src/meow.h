#ifndef rosgolla_meow_h
#define rosgolla_meow_h

#include <stdbool.h>
#include "memory.h"

#define TAPE_SIZE 30000  // Size of the Brainfuck memory tape

bool isMeowings(const char *source);
void runMeow(const char *meowings);
char* parseMeow(const char *meowings);
void runBrainFuck(const char *code);
#endif
