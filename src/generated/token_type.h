#pragma once

enum TokenType {
	// Keywords - lexed
	_RETURN,
	_MARK,
	_GOTO,
	_IF,
	_PRINT_LINE,
	// Operators - to lex
	_OP_EQUALS,
	_OP_ADD,
	_OP_SUB,
	// Literals - to lex
	_INT_LITERAL,
	// Special - to lex
	_IDENTIFIER,
	_STATEMENT_END,
	_TOKENS_END, // lexed
};
