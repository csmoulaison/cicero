#pragma once

enum TokenType {
	// Keywords: must be first in the file  due to their lazy association with the
	//   token_to_keyword_map.
	_KEY_EXIT,
	_KEY_MARK,
	_KEY_GOTO,
	_KEY_IF,
	_KEY_PRINT_LINE,
	// Arithmetic operators
	_OP_ADD,
	_OP_SUB,
	_OP_MULTIPLY, // division too ambiguous. this is assembly+
	// Assignment operators
	_OP_ASSIGN, // :
	// Unary operators
	_OP_LOGICAL_NOT,
	// Comparison operators
	_OP_EQUALS, // =
	_OP_LESS_THAN, // never will there be a less than or equals. unnecessary!
	_OP_GREATER_THAN,
	// Literals
	_BYTE_LITERAL,
	// Special
	_IDENTIFIER,
	_STATEMENT_END,
	_TOKENS_END
};
