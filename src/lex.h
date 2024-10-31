#pragma once
#include <stdint.h>
#include <stdbool.h>

// TODO: This isn't ideal, as the keyword token map is sparse due to using
//   TokenType as indices, and there being more TokenTypes than keywords.
#define KEYWORD_MAX 32
#define KEYWORD_STR_MAX 12
#define NULL_KEYWORD "NOKEY"

enum TokenType {
	// Keywords - lexed
	_RETURN,
	_MARK,
	_GOTO,
	_IF,
	_PRINT_LINE,
	// Operators - to lex
	_OP_EQUALS,
	_OP_ADD,
	_OP_SUB,
	// Literals - to lex
	_INT_LITERAL,
	// Special - to lex
	_IDENTIFIER,
	_STATEMENT_END,
	_TOKENS_END, // lexed
};

struct {
	enum TokenType type;
	void* value;
} typedef Token;

static char g_token_keyword_map[KEYWORD_MAX][KEYWORD_STR_MAX];

void lex_file(const char* src, const uint32_t tokens_max, Token* out_tokens);
static bool try_keyword(const char* src, const char* keyword, uint32_t* out_index);
void init_token_keyword_map();
