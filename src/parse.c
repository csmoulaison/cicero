#include "parse.h"
#include <stdlib.h>

#define PRIORITY_MULTIPLY 4
#define PRIORITY_ADD 3
#define PRIORITY_SUB 2

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
	Expression expression = parse_expression(context, 1);

	if(expression.type == EXPR_WORD) {
		Token* token = consume(context);
		if(token->type != TOKEN_STATEMENT_END) {
			printf("Error: Expected statement end after exit command.\n");
			exit(1);
		}

		fprintf(context->out_file, "mov rdi, %u\n", expression.value.word);
		fprintf(context->out_file, "mov rax, 60\n");
		fprintf(context->out_file, "syscall\n");
	} else {
		printf("Error: Expected word expression when parsing exit.\n");
		exit(1);
	}
}

static Expression parse_expression(ParseContext* context, uint8_t precedence) {
	Token* left_token = consume(context);
	if(left_token->type == TOKEN_WORD_LITERAL) {
		Expression left = (Expression){EXPR_WORD, left_token->value.word};

		while(precedence < peek_precedence(context)) {
			Token* right_token = consume(context);

			Expression right = parse_expression(context, PRIORITY_ADD);
			if(right.type != EXPR_WORD) {
				printf("Error: Expected right hand expression to resolve to a word literal.\n");
				exit(1);
			}

			switch(right_token->type) {
			case TOKEN_ADD:
				left.value.word = left.value.word + right.value.word;
				break;
			case TOKEN_SUB:
				left.value.word = left.value.word - right.value.word;
				break;
			case TOKEN_MULTIPLY:
				left.value.word = left.value.word * right.value.word;
				break;
			default:
				printf("After peeking priority, stil got an invalid token. What's wrong?\n");	
				exit(1);
			}
		}

		return left;
	} else {
		printf("Error: Expected word literal when parsing expression.\n");
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

uint8_t peek_precedence(ParseContext* context) {
	switch(peek(context)->type) {
	case TOKEN_ADD:
		return PRIORITY_ADD;
	case TOKEN_SUB:
		return PRIORITY_SUB;
	case TOKEN_MULTIPLY:
		return PRIORITY_MULTIPLY;
	default:
		break;
	}
	return 0;
}
