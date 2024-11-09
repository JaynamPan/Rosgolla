#ifndef rosgolla_compiler_h
#define rosgolla_compiler_h

#include "vm.h"
#include "object.h"

ObjFunction* compile(const char* source);

#endif
