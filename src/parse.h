#pragma once
#include <stdio.h>
#include <stdint.h>
#include "token.h"

#define ASM_PATH "program.asm"
#define OBJECT_PATH "program.o"
#define EXE_PATH "program"

#define VARS_MAX 256

// This isn't very useful right now, but it will be if we need to implement a
// double pass. For now, I'm not too worried about the additional code
// complexity unnecessarily added for this.
enum ExpressionType {
	EXPR_WORD,
	EXPR_BINARY,
	EXPR_UNARY,
	EXPR_GROUP
};

struct {
	enum ExpressionType type;
	union {
		uint64_t word;
	} value;
} typedef Expression;

struct {
	char identifier[IDENTIFIER_MAX_LEN];
	int32_t offset;
} typedef ParserVariable;

struct {
	Token* tokens;
	uint32_t token_index;
	FILE* out_file;
	ParserVariable vars[VARS_MAX];
	uint32_t vars_len;
} typedef ParseContext;

void parse_and_compile(Token* tokens);
// Top level parsing
static void parse_statement(ParseContext* context);
static void parse_exit(ParseContext* context);
static void parse_word_declaration(ParseContext* context);
static void parse_word_assignment(ParseContext* context, const char* identifier);
// Expressions
static Expression parse_expression(ParseContext* context, uint8_t precedence);
// Helper functions
static Token* peek(ParseContext* context);
static Token* consume(ParseContext* context);
void skip(ParseContext* context);
uint8_t peek_precedence(ParseContext* context);
