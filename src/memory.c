#include <stdlib.h>
#include "memory.h"

void* reallocate(void *pointer, size_t oldCount, size_t newCount){
	// if newCount is 0 then free
	if(newCount == 0){
		free(pointer);
		return NULL;
	}
	void *result = realloc(pointer, newCount);
	if(result == NULL){
		exit(1);
	}
	return result;
}
