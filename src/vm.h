#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include "table.h"
#include "object.h"

#define FRAME_MAX 64
#define STACK_MAX (FRAME_MAX * UINT8_COUNT)
typedef struct {
	ObjFunction *function;
	uint8_t *ip; 
	// store caller's ip 
	// for callee to return to
	Value *slots;
} CallFrame;

typedef struct{
	CallFrame frames[FRAME_MAX];
	int frameCount;
	Value stack[STACK_MAX];
	Value *stackTop;
	Table strings;
	Table globals;
	Obj* objects;
} VM;

typedef enum{
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();
VM vm;
#endif
