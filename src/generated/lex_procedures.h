#pragma once

#define LEX_PROCEDURES_LEN 5

// const char* src, const uint32_t src_index
typedef LexTokenResult(*lex_procedure)(const char* src, uint32_t src_index);

// The order here is intentional.
// Constraints so far:
	// lex_identifier should be after lex_keyword
static lex_procedure lex_procedures[LEX_PROCEDURES_LEN] = {
	lex_statement_end,
	lex_keyword,
	lex_operator,
	lex_int_literal,
	lex_identifier
};
