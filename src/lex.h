#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "generated/token_type.h"

// 10-3-24 lex refactor
// Each token type has an associated lex_ function
// The lexer has a context which gets passed around
// The lexer context contains the token_keyword_map as well as...
// The list of different lex_ functions
// The lex_file dispatches these functions

#define TOKEN_BUF_LEN 4096
// TODO: This isn't ideal, as the keyword token map is sparse due to using
//   TokenType as indices, and there being more TokenTypes than keywords.
#define NULL_KEYWORD "NOKEY"
#define IDENTIFIER_MAX_LEN 63

struct {
	enum TokenType type;
	union {
		uint8_t byte;
		// + 1 because it's a null terminated string
		char string[IDENTIFIER_MAX_LEN + 1];
	} value;
} typedef Token;

struct {
	bool success;
	bool abort;
	uint32_t chars_read;
	Token token;
} typedef LexTokenResult;

void lex_source(const char* src, const uint32_t tokens_max, Token* tokens);
// Added to lex_procedures array of functions and dynamically dispatched.
static LexTokenResult lex_statement_end(const char* src, uint32_t src_index);
static LexTokenResult lex_keyword(const char* src, uint32_t src_index);
static LexTokenResult lex_operator(const char* src, uint32_t src_index);
static LexTokenResult lex_byte_literal(const char* src, uint32_t src_index);
static LexTokenResult lex_identifier(const char* src, uint32_t src_index);
// Helper functions
static bool check_numeric(char c);
