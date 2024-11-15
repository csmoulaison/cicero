#include "parse.h"
#include <stdlib.h>
#include "asm.h"

void parse_program(const Token* tokens) {
	printf("\nParsing and emitting nasm...\n");

	FILE* nasm;
	nasm = fopen(ASM_PATH, "w");

	fprintf(nasm, "global _start\n_start:\n");

	uint32_t token_index = 0;
	while(tokens[token_index].type != TOKEN_PROGRAM_END) {
		parse_statement(tokens, &token_index, nasm);
	}

	fclose(nasm);

	printf("Parsing complete.\n");
}

void parse_statement(const Token* tokens, uint32_t* token_index, FILE* nasm) {
	*token_index += 1;
	switch(tokens[*token_index - 1].type) {
	case TOKEN_EXIT:
		parse_exit(tokens, token_index, nasm);
		break;
	case TOKEN_ASSIGN:
		// TODO: parse assign statement
		printf("Error: Expected exit statement, got assign.\n");
		exit(1);
		parse_assign(tokens, token_index, nasm);
		break;
	case TOKEN_OUT:
		// TODO: parse out statement
		printf("Error: Expected exit statement, got out token.\n");
		exit(1);
		parse_out(tokens, token_index, nasm);
		break;
	default:
		printf("Error: Expected exit statement, got nothing.\n");
		exit(1);
		break;
	}
}

void parse_exit(const Token* tokens, uint32_t* token_index, FILE* nasm) {
	Expression expr = parse_expression(tokens, token_index, nasm);
	if(expr.type == EXPR_BYTE) {
		if(tokens[*token_index].type != TOKEN_STATEMENT_END) {
			printf("Error: Expected statement end after exit command.\n");
		}
		*token_index += 1;
		fprintf(nasm, "mov rdi, %u\n", expr.value.byte);
		fprintf(nasm, "mov rax, 60\n");
		fprintf(nasm, "syscall\n");
	} else {
		printf("Error: Expected byte expression when parsing exit.\n");
		exit(1);
	}
}

void parse_assign(const Token* tokens, uint32_t* token_index, FILE* nasm) {
	// TODO: implement parse_assign
}

void parse_out(const Token* tokens, uint32_t* token_index, FILE* nasm) {
	// TODO: implement parse_out
}

Expression parse_expression(const Token* tokens, uint32_t* token_index, FILE* nasm) {
	Expression expr;
	
	switch(tokens[*token_index].type) {
	case TOKEN_BYTE_LITERAL:
		// TODO: check if followed by operator for binary expr
		expr.type = EXPR_BYTE;
		expr.value.byte = tokens[*token_index].value.byte;
		*token_index += 1;
		break;
	default:
		// TODO: error
		printf("Error: Expected byte literal when parsing expression.\n");
		exit(1);
		break;
	}

	return expr;
}
