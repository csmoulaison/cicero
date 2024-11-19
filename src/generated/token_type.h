#pragma once

enum TokenType {
	// Keywords: must be first in the file  due to their lazy association with the
	//   token_to_keyword_map.
	TOKEN_EXIT,
	TOKEN_MARK,
	TOKEN_JUMP,
	TOKEN_IF,
	TOKEN_OUT,
	// Arithmetic operators
	TOKEN_ADD,
	TOKEN_SUB,
	TOKEN_MULTIPLY, // division too ambiguous. this is assembly+
	// Assignment operators
	TOKEN_ASSIGN, // :
	// Unary operators
	TOKEN_LOGICAL_NOT,
	// Comparison operators
	TOKEN_EQUALS, // =
	TOKEN_LESS_THAN, // never will there be a less than or equals. unnecessary!
	TOKEN_GREATER_THAN,
	// Literals
	TOKEN_WORD_LITERAL,
	// Special
	TOKEN_IDENTIFIER,
	TOKEN_STATEMENT_END,
	TOKEN_PROGRAM_END
};
