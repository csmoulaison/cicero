#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generated/lex_procedures.h"
#include "generated/token_to_keyword_map.h"

// Converts a source file into lexical tokens.
void lex_source(const char* src, Token* tokens) {
	printf("\nStarting lexical analysis...\n");

	uint32_t src_index = 0;
	uint32_t token_index = 0;
	while(src[src_index] != '\0') {
		if(token_index >= TOKENS_MAX) {
			printf("Error: Trying to lex another token, but we have already reached the token max. (%i)\n", TOKENS_MAX);
			goto abort_lexical_analysis;
		}
		
		while(src[src_index] == ' ') {
			src_index++;
		}

		LexTokenResult lex_result;
		for(int proc_index = 0; proc_index < LEX_PROCEDURES_LEN; proc_index++) {
			lex_result = lex_procedures[proc_index](src, src_index);

			if(lex_result.abort) {
				goto abort_lexical_analysis;
			}

			if(lex_result.success) {
				src_index += lex_result.chars_read;
				tokens[token_index] = lex_result.token;
				token_index++;
				break;
			}
		}

		if(!lex_result.success) {
			printf("Error: No valid lexical token at index %i.\n", src_index);
			goto abort_lexical_analysis;
		}
	}

finish_lex_file:
	printf("Lexical analysis complete.\n");
	if(tokens[token_index - 1].type != TOKEN_STATEMENT_END) {
		tokens[token_index] = (Token){TOKEN_STATEMENT_END, 0};
		token_index++;
	}
	tokens[token_index] = (Token){TOKEN_PROGRAM_END, 0};
	return;

abort_lexical_analysis:
	printf("Lexical analysis aborted.\n");
	exit(1);
}


static LexTokenResult lex_statement_end(const char* src, uint32_t src_index) {
	LexTokenResult result;
	result.abort = false;

	if(src[src_index] == '\n') {
		result.success = true;
		result.token = (Token){TOKEN_STATEMENT_END, 0};
		result.chars_read = 1;
		return result;
	}

	result.success = false;
	return result;
}


static LexTokenResult lex_keyword(const char* src, uint32_t src_index) {
	LexTokenResult result;
	result.abort = false;

	result.success = false;
	const uint32_t initial_src_index = src_index;

	// Iterate through keyboard_to_token_map testing for match
	for(uint8_t token_map_index = 0; token_map_index < KEYWORD_LEN; token_map_index++) {
		const char* keyword = token_to_keyword_map[token_map_index];

		// Iterate through keyword string testing for matching characters
		uint8_t keyword_index = 0;
		bool token_matched = true;
		while(keyword[keyword_index] != '\0') {
			bool end_of_token = src[src_index] == '\0' && src[src_index] != ' ';
			bool char_matched = keyword[keyword_index] == src[src_index];

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
	LexTokenResult result;
	result.abort = false;

	switch(src[src_index]) {
	case '+':
		result.token.type = TOKEN_ADD;
		break;
	case '-':
		result.token.type = TOKEN_SUB;
		break;
	case '*':
		result.token.type = TOKEN_MULTIPLY;
		break;
	case ':':
		result.token.type = TOKEN_ASSIGN;
		break;
	case '!':
		result.token.type = TOKEN_LOGICAL_NOT;
		break;
	case '=':
		result.token.type = TOKEN_EQUALS;
		break;
	case '<':
		result.token.type = TOKEN_LESS_THAN;
		break;
	case '>':
		result.token.type = TOKEN_GREATER_THAN;
		break;
	// Is not an operator
	default:
		result.success = false;
		return result;
	}

	// Is an operator
	result.success = true;
	result.chars_read = 1;
	return result;
}


static LexTokenResult lex_byte_literal(const char* src, uint32_t src_index) {
	LexTokenResult result;
	result.token.type = TOKEN_BYTE_LITERAL;
	result.abort = false;

	if(!isdigit(src[src_index])) {
		result.success = false;
		return result;
	}

	// 5 is the maximum characters because byte literals can only be 8 bit ints
	// in range [0..255] and the string is null terminated.
	char buffer[5];
	buffer[0] = src[src_index];

	uint8_t i = 1;
	while(isdigit(src[src_index + i])) {
		if(i >= 3) {
			printf("Error: More than 3 digits in byte literal at index %i. Byte literals can only be in range [0..255].\n", src_index);
			result.abort = true;
			return result;
		}

		buffer[i] = src[src_index + i];
		i++;
	}

	buffer[i] = '\0';

	uint64_t i64_representation = atoi(buffer);
	if(i64_representation > 255) {
		printf("Error: Byte literal %i at index %i larger than the 8 bit limit of 255.\n", i64_representation, src_index);
		result.abort = true;
		return result;
	}

	result.success = true;
	result.chars_read = strlen(buffer);
	result.token.value.byte = i64_representation;
	return result;
}


static LexTokenResult lex_identifier(const char* src, uint32_t src_index) {
	LexTokenResult result;
	result.token.type = TOKEN_IDENTIFIER;
	result.abort = false;

	if(!isalpha(src[src_index])) {
		result.success = false;
		return result;
	}

	// + 1 because the identifier is null terminated
	char* buffer = result.token.value.string;
	buffer[0] = src[src_index];

	uint8_t i = 1;
	while(isalnum(src[src_index + i])) {
		if(i >= IDENTIFIER_MAX_LEN) {
			printf("Error: Identifier at index %i is longer than the max identifier length of %i\n", src_index, IDENTIFIER_MAX_LEN);
			result.abort = true;
			return result;
		}
		
		buffer[i] = src[src_index + i];

		result.success = true;

		i++;
	}
	buffer[i] = '\0';

	result.chars_read = strlen(buffer);
	return result;
}
