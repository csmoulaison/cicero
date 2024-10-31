#pragma once
#include <stdint.h>
#include <stdbool.h>

// TODO: This isn't ideal, as the keyword token map is sparse due to using
//   TokenType as indices, and there being more TokenTypes than keywords.
#define KEYWORD_MAX 32
#define KEYWORD_STR_MAX 12
#define NULL_KEYWORD "NOKEY"

enum TokenType {
	_RETURN,
	_STATEMENT_END,
	_MARK,
	_GOTO,
	_IF,
	_INT_LITERAL,
	_PRINT_LINE,
	_END_PROGRAM
};

struct {
	enum TokenType type;
	void* value;
} typedef Token;

static char g_token_keyword_map[KEYWORD_MAX][KEYWORD_STR_MAX];

void lex(const char* src, const uint32_t tokens_max, Token* out_tokens);
static bool try_keyword(const char* src, const char* keyword, uint32_t* out_index);
void init_token_keyword_map();
