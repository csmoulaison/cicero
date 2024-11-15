// A recursive descent parser is one which just implements the formal grammar
// using imperative code. the tree of function calls matches the tree specified
// by the formal grammer, and the resultant abstract syntax tree.
//
// This is simple.

#pragma once
#include <stdio.h>
#include <stdint.h>
#include "token.h"

#define ASM_PATH "program.asm"
#define OBJECT_PATH "program.o"
#define EXE_PATH "program"

// This isn't actually very useful right now, but it will be if we need to
// implement a double pass. For now, I'm not too worried about the additional
// code complexity unnecessarily added for this.
enum ExpressionType {
	EXPR_BYTE,
	EXPR_BINARY,
	EXPR_UNARY,
	EXPR_GROUP
};

struct {
	enum ExpressionType type;
	union {
		uint8_t byte;
	} value;
} typedef Expression;

// Parses and compiles tokens in a single pass, outputting a final executable
void parse_program(const Token* tokens);
void parse_statement(const Token* tokens, uint32_t* token_index, FILE* nasm);
void parse_exit(const Token* tokens, uint32_t* token_index, FILE* nasm);
void parse_assign(const Token* tokens, uint32_t* token_index, FILE* nasm);
void parse_out(const Token* tokens, uint32_t* token_index, FILE* nasm);
Expression parse_expression(const Token* tokens, uint32_t* token_index, FILE* nasm);
