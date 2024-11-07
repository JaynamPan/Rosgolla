#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "value.h"
#include "memory.h"

void disassembleChunk(Chunk *chunk, const char *name) {
	printf("== %s ==\n", name);

	for(int offset = 0; offset < chunk->count;) {
		offset = disassembleInstruction(chunk, offset);
	}
}

static int simpleInstruction(const char *name, int offset) {
	printf("%s\n", name);
	return offset + 1;
}

static int byteInstruction(const char *name, Chunk *chunk, int offset) {
	uint8_t slot = chunk->code[offset + 1];
	printf("%-16s %4d\n", name, slot);
	return offset + 2;
}

static int jumpInstruction(const char *name, int sign,
                           Chunk *chunk, int offset) {
	uint16_t jump = (uint16_t)(chunk->code[offset + 1] << 8);
	jump |= chunk->code[offset + 2];
	printf("%-16s %4d -> %d\n", name, offset, offset + 3 + sign * jump);
	return offset + 3;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
	uint8_t constant = chunk->code[offset + 1];
	printf("%-16s %4d ", name, constant);
	printValue(chunk->constants.values[constant]);
	printf("\n");
	return offset + 2;
}


void printToken(Token *token) {
	printf("invoked\n");
	char *type;
	switch(token->type) {
		case TOKEN_LEFT_PAREN:
			type = "TOKEN_LEFT_PAREN";
			break;
		case TOKEN_RIGHT_PAREN:
			type = "TOKEN_RIGHT_PAREN";
			break;
		case TOKEN_LEFT_BRACE:
			type = "TOKEN_LEFT_BRACE";
			break;
		case TOKEN_RIGHT_BRACE:
			type = "TOKEN_RIGHT_BRACE";
			break;
		case TOKEN_COMMA:
			type = "TOKEN_COMMA";
			break;
		case TOKEN_DOT:
			type = "TOKEN_DOT";
			break;
		case TOKEN_MINUS:
			type = "TOKEN_MINUS";
			break;
		case TOKEN_PLUS:
			type = "TOKEN_PLUS";
			break;
		case TOKEN_SEMICOLON:
			type = "TOKEN_SEMICOLON";
			break;
		case TOKEN_SLASH:
			type = "TOKEN_SLASH";
			break;
		case  TOKEN_STAR:
			type = "TOKEN_STAR";
			break;
			// One or two character tokens.
		case TOKEN_BANG:
			type = "TOKEN_BANG";
			break;
		case TOKEN_BANG_EQUAL:
			type = "TOKEN_BANG_EQUAL";
			break;
		case TOKEN_EQUAL:
			type = "TOKEN_EQUAL";
			break;
		case TOKEN_EQUAL_EQUAL:
			type = "TOKEN_EQUAL_EQUAL";
			break;
		case TOKEN_GREATER:
			type = "TOKEN_GREATER";
			break;
		case TOKEN_GREATER_EQUAL:
			type = "TOKEN_BANG";
			break;
		case TOKEN_LESS:
			type = "TOKEN_LESS";
			break;
		case TOKEN_LESS_EQUAL:
			type = "TOKEN_LESS_EQUAL";
			break;
			// Literals.
		case TOKEN_IDENTIFIER:
			type = "TOKEN_IDENTIFIER";
			break;
		case TOKEN_STRING :
			type = "TOKEN_STRING";
			break;
		case TOKEN_NUMBER:
			type = "TOKEN_NUMBER";
			break;
			// Keywords.
		case TOKEN_AND:
			type = "TOKEN_AND";
			break;
		case TOKEN_CLASS:
			type = "TOKEN_CLASS";
			break;
		case TOKEN_ELSE:
			type = "TOKEN_ELSE";
			break;
		case TOKEN_FALSE:
			type = "TOKEN_BANG";
			break;
		case TOKEN_FOR:
			type = "TOKEN_FOR";
			break;
		case TOKEN_FUN:
			type = "TOKEN_FUN";
			break;
		case TOKEN_IF:
			type = "TOKEN_IF";
			break;
		case TOKEN_NIL:
			type = "TOKEN_NIL";
			break;
		case TOKEN_OR:
			type = "TOKEN_OR";
			break;
		case TOKEN_PRINT:
			type = "TOKEN_PRINT";
			break;
		case TOKEN_RETURN:
			type = "TOKEN_RETURN";
			break;
		case TOKEN_SUPER:
			type = "TOKEN_BANG";
			break;
		case TOKEN_THIS:
			type = "TOKEN_THIS";
			break;
		case TOKEN_TRUE:
			type = "TOKEN_TRUE";
			break;
		case TOKEN_VAR:
			type = "TOKEN_VAR";
			break;
		case  TOKEN_WHILE:
			type = "TOKEN_WHILE";
			break;
		case TOKEN_ERROR:
			type = "TOKEN_ERROR";
			break;
		case TOKEN_EOF:
			type = "TOKEN_EOF";
			break;
		default:
			type = "Unknown Token";
			break;
	}
	char *content = ALLOCATE(char, token->length + 1);
	strncpy(content, token->start, token->length);
	printf("DEBUG token: type = %s, content = %s \n", type, content);
}

int disassembleInstruction(Chunk *chunk, int offset) {
	printf("%04d ", offset);
	if(offset > 0 &&
	        chunk->lines[offset] == chunk->lines[offset - 1]) {
		printf("   | ");
	} else {
		printf("%4d ", chunk->lines[offset]);
	}
	uint8_t instruction = chunk->code[offset];
	switch(instruction) {
		case OP_RETURN:
			return simpleInstruction("OP_RETURN", offset);
		case OP_CONSTANT:
			return constantInstruction("OP_CONSTANT", chunk, offset);
		case OP_NEGATE:
			return simpleInstruction("OP_NEGATE", offset);
		case OP_ADD:
			return simpleInstruction("OP_ADD", offset);
		case OP_SUBTRACT:
			return simpleInstruction("OP_SUBTRACT", offset);
		case OP_MULTIPLY:
			return simpleInstruction("OP_MULTIPLY", offset);
		case OP_DIVIDE:
			return simpleInstruction("OP_DIVIDE", offset);
		case OP_NIL:
			return simpleInstruction("OP_NIL", offset);
		case OP_TRUE:
			return simpleInstruction("OP_TRUE", offset);
		case OP_FALSE:
			return simpleInstruction("OP_FALSE", offset);
		case OP_NOT:
			return simpleInstruction("OP_NOT", offset);
		case OP_EQUAL:
			return simpleInstruction("OP_EQUAL", offset);
		case OP_GREATER:
			return simpleInstruction("OP_GREATER", offset);
		case OP_PRINT:
			return simpleInstruction("OP_PRINT", offset);
		case OP_LESS:
			return simpleInstruction("OP_LESS", offset);
		case OP_POP:
			return simpleInstruction("OP_POP", offset);
		case OP_DEFINE_GLOBAL:
			return constantInstruction("OP_DEFINE_GLOBAL", chunk, offset);
		case OP_GET_GLOBAL:
			return constantInstruction("OP_GET_GLOBAL", chunk, offset);
		case OP_SET_GLOBAL:
			return constantInstruction("OP_SET_GLOBAL", chunk, offset);
		case OP_SET_LOCAL:
			return byteInstruction("OP_SET_LOCAL", chunk, offset);
		case OP_GET_LOCAL:
			return byteInstruction("OP_GET_LOCAL", chunk, offset);
		case OP_JUMP:
			return jumpInstruction("OP_JUMP", 1, chunk, offset);
		case OP_JUMP_IF_FALSE:
			return jumpInstruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
		case OP_LOOP:
			return jumpInstruction("OP_LOOP", -1, chunk, offset);
		default:
			printf("Unknown opcode %d\n", instruction);
			return offset + 1;

	}
}

