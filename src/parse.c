#include "parse.h"
#include <stdlib.h>
#include <string.h>

#define STACK_ALIGN 16
#define IF_LABEL "CICERO_IF_LABEL"

void parse_and_compile(Token* tokens, const char* out_path) {
	printf("\nParsing and emitting nasm...\n");

	char asm_path[4096];
	sprintf(asm_path, "%s.asm", out_path);

	ParseContext context;
	context.out_file = fopen(asm_path, "w");
	context.tokens = tokens;
	context.token_index = 0;
	context.if_count = 0;
	context.vars_len = 0;
	context.marks_len = 0;
	context.jumps_len = 0;

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

	for(uint32_t jump_index = 0; jump_index < context.jumps_len; jump_index++) {
		if(!context.jumps[jump_index].mark_declared) {
			printf("Error: Jump identifier %s was never declared.\n", context.jumps[jump_index].identifier);
			exit(1);
		}
	}

	fprintf(context.out_file, "section .data\n");
	fprintf(context.out_file, "fmt: db \"%%i\", 10, 0\n");

	fclose(context.out_file);
	printf("Parsing complete.\n");
}

static void parse_statement(ParseContext* context) {
	Token* token = consume(context);

	switch(token->type) {
	case TOKEN_MARK:
		parse_mark(context);
		break;
	case TOKEN_JUMP:
		parse_jump(context);
		break;
	case TOKEN_IF:
		parse_if(context);
		break;
	case TOKEN_EXIT:
		parse_exit(context);
		break;
	case TOKEN_PRINT:
		parse_print(context);
		break;
	case TOKEN_WORD:
		parse_declaration(context);
		break;
	case TOKEN_IDENTIFIER:
		expect(context, TOKEN_ASSIGN, "After identifier");
		parse_assignment(context, token->value.identifier);
		break;
	default:
		printf("Error: Expected a statement, got %i.\n", token->type);
		exit(1);
		break;
	}
}

static void parse_mark(ParseContext* context) {
	Token* mark_token = expect(context, TOKEN_IDENTIFIER, "After mark keyword.");
	expect(context, TOKEN_STATEMENT_END, "During mark command.");

	for(uint64_t mark_index = 0; mark_index < context->marks_len; mark_index++) {
		if(strcmp(context->marks[mark_index], mark_token->value.identifier) == 0) {
			printf("Error: Mark %s already declared.\n", mark_token->value.identifier);
			exit(1);
		}
	}

	for(uint64_t jump_index = 0; jump_index < context->jumps_len; jump_index++) {
		if(strcmp(context->jumps[jump_index].identifier, mark_token->value.identifier) == 0) {
			context->jumps[jump_index].mark_declared = true;
			break;
		}
	}

	strcpy(context->marks[context->marks_len], mark_token->value.identifier);
	context->marks_len++;

	fprintf(context->out_file, "%s:\n", mark_token->value.identifier);
}

static void parse_jump(ParseContext* context) {
	Token* mark_token = expect(context, TOKEN_IDENTIFIER, "After jump keyword");
	expect(context, TOKEN_STATEMENT_END, "During jump command.");

	ParseJump jump;
	strcpy(jump.identifier, mark_token->value.identifier);
	jump.mark_declared = false;

	for(uint64_t mark_index = 0; mark_index < context->marks_len; mark_index++) {
		if(strcmp(context->marks[mark_index], mark_token->value.identifier) == 0) {
			jump.mark_declared = true;
			break;
		}
	}

	fprintf(context->out_file, "JMP %s\n", jump.identifier);
}

static void parse_if(ParseContext* context) {
	expect(context, TOKEN_PAREN_OPEN, "After if keyword");
	Expression left = parse_expression(context, 0);
	Token* operator = consume(context);
	Expression right = parse_expression(context, 0);
	expect(context, TOKEN_PAREN_CLOSE, "After comparison parsed");

	char jump_opcode[4];
	switch(operator->type) {
	case TOKEN_EQUAL:
		strcpy(jump_opcode, "JNE");
		break;
	case TOKEN_NOT_EQUAL:
		strcpy(jump_opcode, "JE");
		break;
	case TOKEN_GREATER_THAN:
		strcpy(jump_opcode, "JL");
		break;
	case TOKEN_LESS_THAN:
		strcpy(jump_opcode, "JG");
		break;
	default:
		printf("Error: Expected comparison operator after expression. In conditional statement\n");
		exit(1);
	}

	fprintf(context->out_file, "mov rax, %s\n", left.reference_string);
	fprintf(context->out_file, "mov rbx, %s\n", right.reference_string);
	fprintf(context->out_file, "cmp rax, rbx\n");
	fprintf(context->out_file, "%s %s%i\n", jump_opcode, IF_LABEL, context->if_count);

	parse_statement(context);

	fprintf(context->out_file, "%s%i:\n", IF_LABEL, context->if_count);
	context->if_count++;
}

static void parse_exit(ParseContext* context) {
	Expression exit_code = parse_expression(context, 1);

	expect(context, TOKEN_STATEMENT_END, "During exit command.");

	fprintf(context->out_file, "mov rdi, %s\n", exit_code.reference_string);
	fprintf(context->out_file, "call exit\n");
}

static void parse_print(ParseContext* context) {
	Expression out_value = parse_expression(context, 1);

	expect(context, TOKEN_STATEMENT_END, "After out command.");

	fprintf(context->out_file, "mov rdi, fmt\n");
	fprintf(context->out_file, "mov rsi, %s\n", out_value.reference_string);
	fprintf(context->out_file, "call printf\n");
}

static void parse_declaration(ParseContext* context) {
	Token* word_token = expect(context, TOKEN_IDENTIFIER, "In word declaration");

	for(uint64_t var_index = 0; var_index < context->vars_len; var_index++) {
		if(strcmp(context->vars[var_index].identifier, word_token->value.identifier) == 0) {
			printf("Error: Variable %s already declared.\n", word_token->value.identifier);
			exit(1);
		}
	}

	context->vars[context->vars_len].offset = (context->vars_len + 1) * -STACK_ALIGN;
	strcpy(context->vars[context->vars_len].identifier, word_token->value.identifier);
	context->vars_len++;

	fprintf(context->out_file, "sub rsp, %i\n", STACK_ALIGN);

	Token* next = consume(context);
	if(next->type == TOKEN_ASSIGN) {
		parse_assignment(context, word_token->value.identifier);
	} else if(next->type != TOKEN_STATEMENT_END) {
		printf("Error: Expected statement end or assignment after word declaration %s.\n", word_token->value.identifier);
		exit(1);
	}
}

static void parse_assignment(ParseContext* context, const char* identifier) {
	ParseVariable* variable = get_variable(context, identifier);

	Expression value = parse_expression(context, 0);

	fprintf(context->out_file, "mov rax, %s\n", value.reference_string);
	fprintf(context->out_file, "mov qword [rbp%i], rax\n", variable->offset);

	expect(context, TOKEN_STATEMENT_END, "After word assignment.");
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
		Token* operator_token = consume(context);

		switch(operator_token->type) {
		case TOKEN_MULTIPLY:
			right_precedence = 3;
			break;
		case TOKEN_DIVIDE:
			right_precedence = 3;
			break;
		case TOKEN_MODULO:
			right_precedence = 3;
			break;
		case TOKEN_SUB:
			right_precedence = 2;
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
			context->token_index--;
			break;
		}

		// Recurse
		Expression right = parse_expression(context, right_precedence);

		// Compile time evaluation
		if(left.type == EXPR_LITERAL && right.type == EXPR_LITERAL) {
			switch(operator_token->type) {
			case TOKEN_MULTIPLY:
				left.value.number = left.value.number * right.value.number;
				break;
			// TODO: Is this consistent with asm functionality?
			case TOKEN_DIVIDE:
				left.value.number = left.value.number / right.value.number;
				break;
			// TODO: Is this consistent with asm functionality?
			case TOKEN_MODULO:
				left.value.number = left.value.number % right.value.number;
				break;
			case TOKEN_SUB:
				left.value.number = left.value.number - right.value.number;
				break;
			case TOKEN_ADD:
				left.value.number = left.value.number + right.value.number;
				break;
			default:
				printf("After peeking priority, stil got an invalid token. What's wrong?\n");	
				exit(1);
			}
		// Runtime evaluation
		} else {
			populate_expression_ref_string(&left);
			fprintf(context->out_file, "mov rax, %s\n", left.reference_string);
			fprintf(context->out_file, "mov rbx, %s\n", right.reference_string);

			char opcode[4];
			switch(operator_token->type) {
			case TOKEN_MULTIPLY:
				fprintf(context->out_file, "mul rbx\n", opcode);
				break;
			case TOKEN_DIVIDE:
				fprintf(context->out_file, "div rbx\n", opcode);
				break;
			case TOKEN_MODULO:
				fprintf(context->out_file, "mov edx, 0\n", opcode);
				fprintf(context->out_file, "div rbx\n", opcode);
				fprintf(context->out_file, "mov eax, edx\n", opcode);
				break;
			case TOKEN_SUB:
				fprintf(context->out_file, "sub rax, rbx\n");
				break;
			case TOKEN_ADD:
				fprintf(context->out_file, "add rax, rbx\n");
				break;
			default:
				printf("E2 After peeking priority, stil got an invalid token. What's wrong?\n");	
			}

			left.type = EXPR_RUNTIME;
		}
	}

	populate_expression_ref_string(&left);
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

static Token* expect(ParseContext* context, enum TokenType expected_type, const char* info) {
	Token* token = consume(context);
	if(token->type != expected_type) {
		printf("Error: Expected %i, got %i. %s.\n", expected_type, token->type, info);
		exit(1);
	}

	return token;
}

static ParseVariable* get_variable(ParseContext* context, const char* identifier) {
	for(uint64_t var_index = 0; var_index < context->vars_len; var_index++) {
		if(strcmp(context->vars[var_index].identifier, identifier) == 0) {
			return &context->vars[var_index];
		}
	}

	printf("Error: Trying to reference variable %s, but it doesn't exist.\n", identifier);
	exit(1);
}

static void populate_expression_ref_string(Expression* expr) {
	switch(expr->type) {
	case EXPR_LITERAL:
		sprintf(expr->reference_string, "%i", expr->value.number);
		break;
	case EXPR_VARIABLE:
		sprintf(expr->reference_string, "[rbp%i]", expr->value.offset);
		break;
	case EXPR_RUNTIME:
		sprintf(expr->reference_string, "rax"); // depends where we put the result here
		break;
	default:
		printf("Compiler Error: Not all expression types caught or type not set when constructing expression reference string.\n");
		exit(1);
	}
}
