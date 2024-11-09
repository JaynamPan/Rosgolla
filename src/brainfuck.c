#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "meow.h"

void runBrainFuck(const char *code) {
	unsigned char tape[TAPE_SIZE] = {0};   // Brainfuck memory tape
	unsigned char *ptr = tape;             // Data pointer
	const char *pc = code;                 // Program counter
	int loop;                              // Loop counter
	
	while (*pc) {
		switch (*pc) {
			case '>':
				ptr++;
				if (ptr >= tape + TAPE_SIZE) {
					fprintf(stderr, "Error: Pointer moved outside tape.\n");
					return;
				}
				break;
			case '<':
				ptr--;
				if (ptr < tape) {
					fprintf(stderr, "Error: Pointer moved outside tape.\n");
					return;
				}
				break;
			case '+':
				(*ptr)++;
				break;
			case '-':
				(*ptr)--;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr = (unsigned char)getchar();
				break;
			case '[':
				if (*ptr == 0) {
					int bracket_count = 1;
					while (bracket_count > 0) {
						pc++;
						if (*pc == '[') bracket_count++;
						if (*pc == ']') bracket_count--;
					}
				}
				break;
			case ']':
				if (*ptr != 0) {
					int bracket_count = 1;
					while (bracket_count > 0) {
						pc--;
						if (*pc == ']') bracket_count++;
						if (*pc == '[') bracket_count--;
					}
				}
				break;
		}
		pc++;
	}
	//last \n
	putchar('\n');
	// end
	char *code_ptr = (char*)code;
	FREE_ARRAY(char, code_ptr, TAPE_SIZE);
}


