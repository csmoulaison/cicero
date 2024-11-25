#pragma once

enum TokenType {
	// VOLATILE: Keywords: must be first in the file  due to their lazy association
	//   with the token_to_keyword_map.
	TOKEN_EXIT,
	TOKEN_MARK,
	TOKEN_JUMP,
	TOKEN_IF,
	TOKEN_PRINT,
	TOKEN_WORD,
	// Operators
	TOKEN_ADD,
	TOKEN_SUB,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_MODULO,
	// Comparison operators
	TOKEN_EQUAL,
	TOKEN_NOT_EQUAL,
	TOKEN_LESS_THAN, // never will there be a less than or equals. unnecessary!
	TOKEN_GREATER_THAN,
	// Assignment operator
	TOKEN_ASSIGN,
	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE,
	// Literals
	TOKEN_WORD_LITERAL,
	// Special
	TOKEN_IDENTIFIER,
	TOKEN_STATEMENT_END,
	TOKEN_PROGRAM_END
};
