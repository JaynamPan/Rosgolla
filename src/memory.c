#include <stdlib.h>
#include "memory.h"
#include "vm.h"

void* reallocate(void *pointer, size_t oldCount, size_t newCount) {
	// if newCount is 0 then free
	if(newCount == 0) {
		free(pointer);
		return NULL;
	}
	void *result = realloc(pointer, newCount);
	if(result == NULL) {
		exit(1);
	}
	return result;
}

static void freeObject(Obj *object) {
	switch(object->type) {
		case OBJ_STRING: {
			ObjString *string = (ObjString*) object;
			FREE_ARRAY(char, string->chars, string->length + 1);
			FREE(OBJ_STRING, object);
			break;
		}
		case OBJ_FUNCTION: {
			ObjFunction *function = (ObjFunction*) object;
			freeChunk(&function->chunk);
			FREE(ObjFunction, object);
			break;
		}
		case OBJ_NATIVE:{
			FREE(ObjNative, object);
			break;
		}
	}
}

void freeObjects() {
	Obj *obj = vm.objects;
	while(obj->next != NULL) {
		Obj *next = obj->next;
		freeObject(obj);
		obj = next;
	}
}

