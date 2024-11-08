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
	}
}

void freeObjects() {
	Obj *obj = vm.objects;
	if(obj == NULL) {
		return;
		// TODO: I added this to fix the bug:
		// when run program in repl it would exit nicely,
		// but when runing a file it seems vm.objects would
		// be null if there's no global vars.
	}
	while(obj->next != NULL) {
		Obj *next = obj->next;
		freeObject(obj);
		obj = next;

	}
}

