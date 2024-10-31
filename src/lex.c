#include "lex.h"
#include <stdio.h>
#include <string.h>

// Converts a source file into lexical tokens.
void lex_file(const char* src, const uint32_t tokens_max, Token* out_tokens) {
	// Initialize global map of keyword string/token type pairs in order to easily
	//   check for hardcoded keyword strings during lexical analysis.
	init_token_keyword_map();
	
	uint32_t tokens_len = 0;
	uint32_t src_index = 0;
	while(src[src_index] != '\0') {
		// Skip whitepace
		while(src[src_index] == ' ') {
			src_index++;
		}

		if(src[src_index] == '\n') {
			out_tokens[tokens_len] = (Token){_STATEMENT_END, NULL};
			tokens_len++;
		}
		
		// Check if next token is a keyword.
		uint8_t token_map_index = 0;
		// Iterate through a global map of keyword string/token type pairs, looking
		//   for a match.
		while(token_map_index != KEYWORD_MAX) {	
			if(g_token_keyword_map[token_map_index] == NULL_KEYWORD) {
				printf("NULL KEYWORD check\n");
				token_map_index++;
				continue;
			}
			
			if(try_keyword(src, g_token_keyword_map[token_map_index], &src_index)) {
				out_tokens[tokens_len] = (Token){token_map_index, NULL};
				tokens_len++;

				printf("Keyword found '%s'\n", g_token_keyword_map[token_map_index]);

				break;
			}

			token_map_index++;
		}
	}

	// _TOKENS_END serves as the null-terminator marking the end of the tokens
	out_tokens[tokens_len] = (Token){_TOKENS_END, NULL};
}

void lex_token() {
	// Put some of the above mess in here. Let's try to SOME compartmentalization with this one?
}

// Returns 1 on matched keyword, 1 if not matched.
// "Consumes" the keyword if matched, mutating the current index into src.
static bool try_keyword(const char* src, const char* keyword, uint32_t* out_index) {
	uint8_t keyword_index = 0;
	uint32_t src_index = *out_index;
	
	while(keyword[keyword_index] != '\0') {
		// If we reach the end of the token without matching:
		if(src[src_index] == '\0' && src[src_index] != ' ') {
			//printf("end of src\n  src: &i\n", src_index);
			return false;
		}

		// If the current chars don't match:
		if(keyword[keyword_index] != src[src_index]) {
			//printf("chars dont match!\n  keyword: %i\n  src: %i\n", keyword_index, src_index);
			return false;
		}

		keyword_index++;
		src_index++;
	}

	// If match found:
	*out_index = src_index;
	return true;
}

// Stores token keyword string pairs in the global map of keyword string/token
//   type pairs
void init_token_keyword_map() {
	for(int i = 0; i <= KEYWORD_MAX; i++) {
		strcpy(g_token_keyword_map[i], NULL_KEYWORD);
	}
	
	strcpy(g_token_keyword_map[_RETURN], "return");
	strcpy(g_token_keyword_map[_MARK], "mark");
	strcpy(g_token_keyword_map[_GOTO], "goto");
	strcpy(g_token_keyword_map[_IF], "if");
	strcpy(g_token_keyword_map[_PRINT_LINE], "printline");
}
