#ifndef ros_chunk_h
#define ros_chunk_h

#include "common.h"
#include "value.h"

typedef enum{
	OP_RETURN,
	OP_NEGATE,
	OP_CONSTANT,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_EQUAL,
	OP_LESS,
	OP_GREATER,
	OP_NIL,
	OP_TRUE,
	OP_FALSE,
	OP_NOT,
} OpCode; 

typedef struct{
	int count;
	int capacity;
	int *lines;
	uint8_t  *code;
	ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);
#endif


