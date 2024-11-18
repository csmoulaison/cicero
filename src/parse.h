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

// This isn't very useful right now, but it will be if we need to implement a
// double pass. For now, I'm not too worried about the additional code
// complexity unnecessarily added for this.
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

struct {
	Token* tokens;
	uint32_t token_index;
	FILE* out_file;
} typedef ParseContext;

void parse_and_compile(Token* tokens);
// Top level parsing
static void parse_statement(ParseContext* context);
static void parse_exit(ParseContext* context);
// static void parse_assign(ParseContext* context);
// Expressions
static Expression parse_expression(ParseContext* context, uint8_t priority);
// Helpers
static Token* peek(ParseContext* context);
static Token* consume(ParseContext* context);
void skip(ParseContext* context);
