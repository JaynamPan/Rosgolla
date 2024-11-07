#ifndef clox_memory_h
#define clox_memory_h

#include "object.h"
#include "common.h"
#define GROW_CAPACITY(capacity) (capacity < 8 ? 8 : (capacity * 2))
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
	((type*)reallocate(pointer, sizeof(type) * oldCount, \
	sizeof(type) * newCount))
#define FREE_ARRAY(type, pointer, oldSize) \
	 (reallocate(pointer, sizeof(type) * (oldSize), 0))
void *reallocate(void *pointer, size_t oldCount, size_t newCount);
void freeObjects();
#define FREE(type, pointer) (reallocate(pointer, sizeof(type), 0))
#define ALLOCATE(type, count) \
	(type*) reallocate(NULL, 0, sizeof(type) * count)
#endif


