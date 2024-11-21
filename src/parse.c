#include "parse.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PRIORITY_MULTIPLY 4
#define PRIORITY_ADD 3
#define PRIORITY_SUB 2
#define BYTE_ALIGNMENT 8

void parse_and_compile(Token* tokens) {
	printf("\nParsing and emitting nasm...\n");

	ParseContext context;
	context.tokens = tokens;
	context.token_index = 0;
	context.out_file = fopen(ASM_PATH, "w");
	context.vars_len = 0;

	fprintf(context.out_file, "global _start\n");
	fprintf(context.out_file, "_start:\n");
	fprintf(context.out_file, "push rbp\n");
	fprintf(context.out_file, "mov rbp, rsp\n");

	while(peek(&context)->type != TOKEN_PROGRAM_END) {
		parse_statement(&context);
		/* TODO: hmm....
		if(peek(&context)->type == TOKEN_STATEMENT_END) {
			context.token_index++;
		}*/
	}

	fclose(context.out_file);
	printf("Parsing complete.\n");
}

static void parse_statement(ParseContext* context) {
	Token* token = consume(context);
	switch(token->type) {
	case TOKEN_EXIT:
		parse_exit(context);
		break;
	case TOKEN_WORD:
		parse_word_declaration(context);
		break;
	case TOKEN_IDENTIFIER:
		if(consume(context)->type != TOKEN_ASSIGN) {
			printf("Error: Expected assignemnt operator after identifier %s.\n", token->value.identifier);
			exit(1);
		}
		parse_word_assignment(context, token->value.identifier);
		break;
	default:
		printf("Error: Expected statement, got %i.\n", token->type);
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

static void parse_word_declaration(ParseContext* context) {
	Token* word_token = consume(context);
	if(word_token->type != TOKEN_IDENTIFIER) {
		printf("Error: Expected identifier in word declaration.\n");
		exit(1);
	}

	for(uint64_t var_index = 0; var_index < context->vars_len; var_index++) {
		if(strcmp(context->vars[var_index].identifier, word_token->value.identifier) == 0) {
			printf("Error: Identifier %s already declared.\n", word_token->value.identifier);
			exit(1);
		}
	}

	context->vars[context->vars_len].offset = (context->vars_len + 1) * -BYTE_ALIGNMENT;
	memcpy(context->vars[context->vars_len].identifier, word_token->value.identifier, IDENTIFIER_MAX_LEN);
	context->vars_len++;

	fprintf(context->out_file, "sub rsp, %i\n", BYTE_ALIGNMENT);

	Token* next_token = consume(context);
	if(next_token->type == TOKEN_ASSIGN) {
		parse_word_assignment(context, word_token->value.identifier);
	} else if(next_token->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end or assignment after word declaration %s.\n", word_token->value.identifier);
		exit(1);
	}
}

static void parse_word_assignment(ParseContext* context, const char* identifier) {
	int32_t offset;
	bool identifier_found = false;

	for(uint64_t var_index = 0; var_index < context->vars_len; var_index++) {
		if(strcmp(context->vars[var_index].identifier, identifier) == 0) {
			identifier_found = true;
			offset = context->vars[var_index].offset;
			break;
		}
	}

	if(!identifier_found) {
		printf("Error: Identifier %s doesn't exist, but you are trying to assign to it.\n", identifier);
		exit(1);
	}

	Token* value_token = consume(context);

	if(value_token->type != TOKEN_WORD_LITERAL) {
		printf("Error: Expected a word literal after assignment operator for identifier %s.\n", identifier);
		exit(1);
	}

	printf("offset %i\n", offset);
	fprintf(context->out_file, "mov qword [rbp%i], %i\n", offset, value_token->value.word);

	Token* statement_end = consume(context);
	if(statement_end->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end after word assignment %s.\n", identifier);
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
