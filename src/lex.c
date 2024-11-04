#include "lex.h"
#include <stdio.h>
#include <string.h>
#include "generated/consume_procedures.h"

// Converts a source file into lexical tokens.
void lex_file(const char* src, const uint32_t tokens_max, Token* tokens) {
	uint32_t src_index = 0;
	uint32_t tokens_index = 0;
	while(src[src_index] != '\0') {
		if(tokens_index >= tokens_max) {
			printf("Trying to find another token, but we have already reached the token max! (%i)", tokens_max);
		}
		
		while(src[src_index] == ' ') {
			src_index++;
		}

		ConsumeTokenRes consume_res;
		for(int proc_index = 0; proc_index < CONSUME_PROCEDURES_LEN; proc_index++) {
			consume_res = consume_procedures[proc_index](src);

			if(consume_res.success) {
				src_index += consume_res.chars_read;
				tokens[tokens_index] = consume_res.token;
				tokens_index++;
			}
		}
	}



	

	
	uint32_t src_index = 0;
	while(src[src_index] != '\0') {
		// Skip whitepace
		while(src[src_index] == ' ') {
			src_index++;
		}

		if(src[src_index] == '\n') {
			out_tokens[tokens_len] = (Token){_STATEMENT_END, NULL};
			tokens_len++;
			src_index++;
		}

		if(try_keyword(src, &src_index)) {

		}
		
		
	}

	// _TOKENS_END serves as the null-terminator marking the end of the tokens
	out_tokens[tokens_len] = (Token){_TOKENS_END, NULL};
}

static ConsumeTokenRes consume_statement_end(const char* src) {
	ConsumeTokenRes res;


	res.success = false;
	return res
}

static ConsumeTokenRes consume_keyword(const char* src, const uint32_t src_index) {
	ConsumeTokenRes res;
	const uint32_t initial_src_index = src_index;
	
	// Check if next token is a keyword.
	uint8_t token_map_index = 0;
	// Iterate through a global map of keyword string/token type pairs, looking
	//   for a match.
	while(token_map_index != KEYWORD_MAX) {	
		if(token_to_keyword_map[token_map_index] == NULL_KEYWORD) {
			token_map_index++;
			continue;
		}

		// Check for one of the keywords
		uint8_t keyword_index = 0;
		while(keyword[keyword_index] != '\0') {
			// If we reach the end of the token without matching:
			if(src[src_index] == '\0' && src[src_index] != ' ') {
				res.success = false;
				return res;
			}

			// If the current chars don't match:
			if(keyword[keyword_index] != src[src_index]) {
				res.success = false;
				return res;
			}

			keyword_index++;
			src_index++;
		}

		// If match found:
		*out_index = src_index;
		return true;

		if(try_keyword(src, token_to_keyword_map[token_map_index], &src_index)) {
			tokens[tokens_len] = (Token){token_map_index, NULL};
			tokens_len++;

			printf("Keyword found '%s'\n", token_to_keyword_map[token_map_index]);

			break;
		}

		token_map_index++;
	}

}

static ConsumeTokenRes consume_operator(const char* src) {
	// TODO: Implement
	// ...

	ConsumeTokenRes res;
	res.success = false;
	return res
}

static ConsumeTokenRes consume_int_literal(const char* src) {
	// TODO: Implement
	// ...

	ConsumeTokenRes res;
	res.success = false;
	return res
}

static ConsumeTokenRes consume_identifier(const char* src) {
	// TODO: Implement
	// ...

	ConsumeTokenRes res;
	res.success = false;
	return res
}
