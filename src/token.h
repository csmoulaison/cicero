#pragma once
#include "token_type.h"

#define IDENTIFIER_MAX_LEN 32

struct {
	enum TokenType type;
	union {
		uint64_t word;
		char identifier[IDENTIFIER_MAX_LEN];
	} value;
} typedef Token;

