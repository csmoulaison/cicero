// Still need to generate.
#pragma once

#define KEYWORD_LEN 6
#define KEYWORD_STR_MAX 12

// Coincides with the order of TokenType, allowing us to iterate
// through all the TokenTypes looking for a keyword match.
// The TokenTypes must also have all of the keywords at the start for this to work.
static char token_to_keyword_map[KEYWORD_LEN][KEYWORD_STR_MAX] = {
	"exit",
	"mark",
	"goto",
	"if",
	"out",
	"word"
};
