#pragma once
#include "generated/token_type.h"

#define IDENTIFIER_MAX_LEN 63

struct {
	enum TokenType type;
	union {
		uint8_t byte;
		// + 1 because it's a null terminated string
		char string[IDENTIFIER_MAX_LEN + 1];
	} value;
} typedef Token;
