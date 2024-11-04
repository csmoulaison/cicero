#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "generated/token_type.h"

// 10-3-24 lex refactor
// Each token type has an associated consume_ function
// The lexer has a context which gets passed around
// The lexer context contains the token_keyword_map as well as...
// The list of different consume_ functions
// The lex_file dispatches these functions

#define TOKEN_BUF_LEN 4096
// TODO: This isn't ideal, as the keyword token map is sparse due to using
//   TokenType as indices, and there being more TokenTypes than keywords.
#define KEYWORD_MAX 32
#define KEYWORD_STR_MAX 12
#define NULL_KEYWORD "NOKEY"

struct {
	enum TokenType type;
	union {
		int64_t int;

	} value;
} typedef Token;

struct {
	uint8_t success;
	uint32_t chars_read;
	Token token;
} typedef ConsumeTokenRes;

void lex_file(const char* src, const uint32_t tokens_max, Token* out_tokens);

// Added to consume_procedures array of functions and dynamically dispatched.
static ConsumeTokenRes consume_statement_end(const char* src);
static ConsumeTokenRes consume_keyword(const char* src);
static ConsumeTokenRes consume_operator(const char* src);
static ConsumeTokenRes consume_int_literal(const char* src);
static ConsumeTokenRes consume_identifier(const char* src);
