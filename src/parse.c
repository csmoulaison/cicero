#include "parse.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_ALIGN 16

void parse_and_compile(Token* tokens) {
	printf("\nParsing and emitting nasm...\n");

	ParseContext context;
	context.tokens = tokens;
	context.token_index = 0;
	context.out_file = fopen(ASM_PATH, "w");
	context.vars_len = 0;

	fprintf(context.out_file, "section .text\n");

	fprintf(context.out_file, "extern printf\n");
	fprintf(context.out_file, "extern exit\n");

	fprintf(context.out_file, "global main\n");
	fprintf(context.out_file, "main:\n");
	fprintf(context.out_file, "push rbp\n");
	fprintf(context.out_file, "mov rbp, rsp\n");

	while(peek(&context)->type != TOKEN_PROGRAM_END) {
		parse_statement(&context);
	}

	fprintf(context.out_file, "section .data\n");
	fprintf(context.out_file, "fmt: db \"%%i\", 10, 0\n");

	fclose(context.out_file);
	printf("Parsing complete.\n");
}

static void parse_statement(ParseContext* context) {
	Token* token = consume(context);

	switch(token->type) {
	case TOKEN_EXIT:
		parse_exit(context);
		break;
	case TOKEN_OUT:
		parse_out(context);
		break;
	case TOKEN_WORD:
		parse_declaration(context);
		break;
	case TOKEN_IDENTIFIER:
		if(consume(context)->type != TOKEN_ASSIGN) {
			printf("Error: Expected assignemnt operator after identifier %s.\n", token->value.identifier);
			exit(1);
		}
		parse_assignment(context, token->value.identifier);
		break;
	default:
		printf("Error: Expected statement, got %i.\n", token->type);
		exit(1);
		break;
	}
}

static void parse_exit(ParseContext* context) {
	Expression exit_code = parse_expression(context, 1);

	char expr_ref_str[EXPR_REF_STR_MAX];
	get_expression_ref_string(&exit_code, expr_ref_str);

	Token* next = consume(context);
	if(next->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end after exit command. Got %i.\n", next->type);
		exit(1);
	}

	//fprintf(context->out_file, "push qword %s\n", expr_ref_str);
	fprintf(context->out_file, "mov rdi, %s\n", expr_ref_str);
	fprintf(context->out_file, "call exit\n");
}

static void parse_out(ParseContext* context) {
	Expression out_value = parse_expression(context, 1);

	char expr_ref_str[EXPR_REF_STR_MAX];
	get_expression_ref_string(&out_value, expr_ref_str);

	Token* next = consume(context);
	if(next->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end after print command. Got %i.\n", next->type);
		exit(1);
	}

	fprintf(context->out_file, "mov rdi, fmt\n");
	fprintf(context->out_file, "mov rsi, %s\n", expr_ref_str);
	fprintf(context->out_file, "call printf\n");
}

static void parse_declaration(ParseContext* context) {
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

	context->vars[context->vars_len].offset = (context->vars_len + 1) * -STACK_ALIGN;
	strcpy(context->vars[context->vars_len].identifier, word_token->value.identifier);
	context->vars_len++;

	fprintf(context->out_file, "sub rsp, %i\n", STACK_ALIGN);

	Token* next_token = consume(context);
	if(next_token->type == TOKEN_ASSIGN) {
		parse_assignment(context, word_token->value.identifier);
	} else if(next_token->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end or assignment after word declaration %s.\n", word_token->value.identifier);
		exit(1);
	}
}

static void parse_assignment(ParseContext* context, const char* identifier) {
	ParseVariable* variable = get_variable(context, identifier);

	Expression value = parse_expression(context, 0);

	char ref_string[EXPR_REF_STR_MAX];
	get_expression_ref_string(&value, ref_string);

	fprintf(context->out_file, "mov rax, %s\n", ref_string);
	fprintf(context->out_file, "mov qword [rbp%i], rax\n", variable->offset);

	Token* statement_end = consume(context);
	if(statement_end->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end after word assignment %s.\n", identifier);
		exit(1);
	}
}

static Expression parse_expression(ParseContext* context, uint8_t precedence) {
	Token* left_token = consume(context);
	Expression left;
	
	switch(left_token->type) {
	case TOKEN_WORD_LITERAL:
		left.type = EXPR_LITERAL;
		left.value.number = left_token->value.word;
		break;
	case TOKEN_IDENTIFIER:
		left.type = EXPR_VARIABLE;
		left.value.offset = get_variable(context, left_token->value.identifier)->offset;
		break;
	default:
		printf("Error: Expected literal or identifier when parsing expression.\n");
		exit(1);
	}

	for(;;) {
		int right_precedence;
		Token* operator_token = peek(context);

		switch(operator_token->type) {
		case TOKEN_MULTIPLY:
			right_precedence = 4;
			break;
		case TOKEN_SUB:
			right_precedence = 3;
			break;
		case TOKEN_ADD:
			right_precedence = 2;
			break;
		default: // nothing more to parse!
			right_precedence = 0;
			break;
		}

		if(right_precedence <= precedence) {
			// Don't recurse
			break;
		}

		context->token_index++;
		// Recurse
		Expression right = parse_expression(context, right_precedence);

		if(left.type == EXPR_LITERAL && right.type == EXPR_LITERAL) {
			// Two compile-time-calculated expressions can operated on at compile time
			switch(operator_token->type) {
			case TOKEN_MULTIPLY:
				left.value.number = left.value.number * right.value.number;
				break;
			case TOKEN_SUB:
				left.value.number = left.value.number - right.value.number;
				break;
			case TOKEN_ADD:
				left.value.number = left.value.number + right.value.number;
				break;
			default:
				printf("E1 After peeking priority, stil got an invalid token. What's wrong?\n");	
				exit(1);
			}
		} else {
			// If one or more of the two expressions is not compile-time-calculated,
			// the relevant calculations are written in asm and pushed on the stack.
			char opcode[4];
			switch(operator_token->type) {
			case TOKEN_MULTIPLY:
				strcpy(opcode, "mul");
				break;
			case TOKEN_SUB:
				strcpy(opcode, "sub");
				break;
			case TOKEN_ADD:
				strcpy(opcode, "add");
				break;
			default:
				printf("E2 After peeking priority, stil got an invalid token. What's wrong?\n");	
			}

			Expression* expressions[2] = { &left, &right };
			char op_registers[2][4] = {"rax", "rbx"};
			char expr_asm_strings[2][EXPR_REF_STR_MAX];

			for(uint8_t i = 0; i < 2; i++) {
				Expression* expr = expressions[i];
				get_expression_ref_string(expr, expr_asm_strings[i]);
				fprintf(context->out_file, "mov %s, %s\n", op_registers[i], expr_asm_strings[i]);
			}

			if(operator_token->type != TOKEN_MULTIPLY) {
				fprintf(context->out_file, "%s rax, rbx\n", opcode);
			} else {
				fprintf(context->out_file, "mul rbx\n", opcode);
			}
			left.type = EXPR_RUNTIME;
		}
	}

	return left;
}

static Token* peek(ParseContext* context) {
	return &context->tokens[context->token_index];
}

static Token* consume(ParseContext* context) {
	Token* token = peek(context);
	context->token_index++;
	return token;
}

static ParseVariable* get_variable(ParseContext* context, const char* identifier) {
	for(uint64_t var_index = 0; var_index < context->vars_len; var_index++) {
		if(strcmp(context->vars[var_index].identifier, identifier) == 0) {
			return &context->vars[var_index];
		}
	}

	printf("Error: Trying to parse variable %s, but it doesn't exist.\n", identifier);
	exit(1);
}

static void get_expression_ref_string(Expression* expr, char out_ref_str[EXPR_REF_STR_MAX]) {
	switch(expr->type) {
	case EXPR_LITERAL:
		sprintf(out_ref_str, "%i", expr->value.number);
		break;
	case EXPR_VARIABLE:
		sprintf(out_ref_str, "[rbp%i]", expr->value.offset);
		break;
	case EXPR_RUNTIME:
		sprintf(out_ref_str, "rax"); // depends where we put the result here
		break;
	default:
		printf("Compiler Error: Not all expression types caught or type not set when constructing expression reference string.\n");
		exit(1);
	}
}
