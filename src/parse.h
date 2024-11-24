#pragma once
#include <stdio.h>
#include <stdint.h>
#include "token.h"

#define ASM_PATH "program.asm"
#define OBJECT_PATH "program.o"
#define EXE_PATH "program"
#define EXPR_REF_STR_MAX 32

#define VARS_MAX 256

enum ExpressionType {
	EXPR_LITERAL,
	EXPR_VARIABLE,
	EXPR_RUNTIME
};

struct {
	enum ExpressionType type;
	union {
		uint64_t number;
		uint64_t offset;
	} value;
	char reference_string[EXPR_REF_STR_MAX];
} typedef Expression;

struct {
	char identifier[IDENTIFIER_MAX_LEN];
	int32_t offset;
} typedef ParseVariable;

struct {
	Token* tokens;
	uint32_t token_index;
	FILE* out_file;
	ParseVariable vars[VARS_MAX];
	uint32_t vars_len;
} typedef ParseContext;

void parse_and_compile(Token* tokens);
// Top level parsing
static void parse_statement(ParseContext* context);
static void parse_exit(ParseContext* context);
static void parse_out(ParseContext* context);
static void parse_declaration(ParseContext* context);
static void parse_assignment(ParseContext* context, const char* identifier);
// Expressions
static Expression parse_expression(ParseContext* context, uint8_t precedence);
// Helper functions
static Token* peek(ParseContext* context);
static Token* consume(ParseContext* context);
static Token* expect(ParseContext* context, enum TokenType expected_type, const char* info);
static ParseVariable* get_variable(ParseContext* context, const char* identifier);
static void populate_expression_ref_string(Expression* expr);
