#ifndef rosgolla_debug_h
#define rosgolla_debug_h
#include "chunk.h"
#include "scanner.h"

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);
void printToken(Token *token);

#endif
