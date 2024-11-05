#include "lex.h"
#include <stdio.h>
#include <string.h>
#include "generated/lex_procedures.h"
#include "generated/token_to_keyword_map.h"

// Converts a source file into lexical tokens.
void lex_file(const char* src, const uint32_t tokens_max, Token* tokens) {
	uint32_t src_index = 0;
	uint32_t token_index = 0;
	while(src[src_index] != '\0') {
		printf("keep reading\n");
		
		if(token_index >= tokens_max) {
			printf("Error: Trying to lex another token, but we have already reached the token max! (%i)\n", tokens_max);
			goto finish_lex_file;
		}
		
		while(src[src_index] == ' ') {
			printf("  skip\n");
			src_index++;
		}

		LexTokenResult lex_result;
		for(int proc_index = 0; proc_index < LEX_PROCEDURES_LEN; proc_index++) {
			printf("  iterate procs\n");
			lex_result = lex_procedures[proc_index](src, src_index);

			if(lex_result.success) {
				printf("    (procs success)\n");
				src_index += lex_result.chars_read;
				tokens[token_index] = lex_result.token;
				token_index++;
				break;
			}
		}

		if(!lex_result.success) {
			printf("Error: no valid lexical token at index %i!\n", src_index);
			goto finish_lex_file;
		}
	}

finish_lex_file:
	// _TOKENS_END serves as the null-terminator marking the end of the tokens
	tokens[token_index] = (Token){_TOKENS_END, 0};
}

static LexTokenResult lex_statement_end(const char* src, uint32_t src_index) {
	LexTokenResult result;

	if(src[src_index] == '\n') {
		result.success = true;
		result.token = (Token){_STATEMENT_END, 0};
		result.chars_read = 1;
		return result;
	}

	result.success = false;
	return result;
}

static LexTokenResult lex_keyword(const char* src, uint32_t src_index) {
	LexTokenResult result;
	result.success = false;
	const uint32_t initial_src_index = src_index;

	// Iterate through keyboard_to_token_map testing for match
	for(uint8_t token_map_index = 0; token_map_index < KEYWORD_LEN; token_map_index++) {
		const char* keyword = token_to_keyword_map[token_map_index];

		// Iterate through keyword string testing for matching characters
		uint8_t keyword_index = 0;
		bool token_matched = true;
		while(keyword[keyword_index] != '\0') {
			bool end_of_token = (src[src_index] == '\0' && src[src_index] != ' ');
			bool char_matched = (keyword[keyword_index] == src[src_index]);

			if(end_of_token || !char_matched) {
				token_matched = false;
				break;
			}

			keyword_index++;
			src_index++;
		}

		if(!token_matched) {
			src_index = initial_src_index;
			continue;
		}

		result.success = true;
		result.chars_read = src_index - initial_src_index;
		result.token = (Token){token_map_index, 0};
	}
	
	return result;
}

static LexTokenResult lex_operator(const char* src, uint32_t src_index) {
	// TODO: Implement
	// ...

	LexTokenResult result;
	result.success = false;
	return result;
}

static LexTokenResult lex_int_literal(const char* src, uint32_t src_index) {
	// TODO: Implement
	// ...

	LexTokenResult result;
	result.success = false;
	return result;
}

static LexTokenResult lex_identifier(const char* src, uint32_t src_index) {
	// TODO: Implement
	// ...

	LexTokenResult result;
	result.success = false;
	return result;
}
