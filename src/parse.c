#include "parse.h"
#include <stdlib.h>

#define PRIORITY_MULTIPLY 2
#define PRIORITY_ADD 1
#define PRIORITY_SUB 0

void parse_and_compile(Token* tokens) {
	printf("\nParsing and emitting nasm...\n");

	ParseContext context;
	context.tokens = tokens;
	context.token_index = 0;
	context.out_file = fopen(ASM_PATH, "w");

	fprintf(context.out_file, "global _start\n_start:\n");

	while(peek(&context)->type != TOKEN_PROGRAM_END) {
		parse_statement(&context);
	}

	fclose(context.out_file);
	printf("Parsing complete.\n");
}

static void parse_statement(ParseContext* context) {
	switch(consume(context)->type) {
	case TOKEN_EXIT:
		parse_exit(context);
		break;
	case TOKEN_ASSIGN:
		// TODO: parse assign statement
		//parse_assign(context);
		// break
		printf("Error: Expected exit statement, got assign.\n");
		exit(1);
	default:
		printf("Error: Expected exit statement, got nothing.\n");
		exit(1);
		break;
	}
}

static void parse_exit(ParseContext* context) {
	Expression expression = parse_expression(context, 0);

	if(expression.type == EXPR_BYTE) {
		Token* token = consume(context);
		if(token->type != TOKEN_STATEMENT_END) {
			printf("Error: Expected statement end after exit command.\n");
			exit(1);
		}

		fprintf(context->out_file, "mov rdi, %u\n", expression.value.byte);
		fprintf(context->out_file, "mov rax, 60\n");
		fprintf(context->out_file, "syscall\n");
	} else {
		printf("Error: Expected byte expression when parsing exit.\n");
		exit(1);
	}
}

static Expression parse_expression(ParseContext* context, uint8_t priority) {
	Token* token = consume(context);
	if(token->type == TOKEN_BYTE_LITERAL) {
		Expression left = (Expression){EXPR_BYTE, token->value.byte};

		if(peek(context)->type == TOKEN_ADD) {
			skip(context);
			Expression right = parse_expression(context, PRIORITY_ADD);

			if(right.type != EXPR_BYTE) {
				printf("Error: Expected right hand expression to resolve to a byte literal.\n");
				exit(1);
			}

			left.value.byte = left.value.byte + right.value.byte;
		}

		return left;
	} else {
		printf("Error: Expected byte literal when parsing expression.\n");
		exit(1);
	}
}

static Token* peek(ParseContext* context) {
	return &context->tokens[context->token_index];
}

static Token* consume(ParseContext* context) {
	Token* token = peek(context);
	context->token_index++;
	return token;
}

void skip(ParseContext* context) {
	context->token_index++;
}
