#pragma once

// Still need to generate.
// Coincides with the order of TokenType, allowing us to iterate
// through all the TokenTypes looking for a keyword match
static char token_to_keyword_map[KEYWORD_MAX][KEYWORD_STR_MAX] {
	"return",
	"mark",
	"goto",
	"if",
	"print_line"
}
