#include <stdio.h>
#include "file.h"
#include "lex.h"

#define TOKENS_MAX 512
#define SRC_MAX 8192

// Agenda: parse tree somehwere in here
// - Parse 'return <int> (newline)' statement
// - Lex / parse printline
// ---
// - Lex operators
// - Parse arithmetic operations with int literals
// ---
// - Lex identifiers
// - Store (print) variables
// - Arithmetic on variables
// ---
// - Marks and jumps
// ---
// - Conditional jumps
// ---
// - Any more operators?
// ---
// - Make a toy project (calculator? idk, something that only uses numbers

int main(int argc, const char** argv) {
	// Error check: wrong number of arguments
	if(argc != 2) {
		printf("Error: Expected 1 argument, and you gave %i. You need to specify the source file. (e.g. 'cicero <input.ci>') \n", argc - 1);
		return 1;
	}

	printf("Compiling...\n");

	// Read file
	char src[SRC_MAX];
	file_to_string(argv[1], SRC_MAX, src);

	// Lexical analysis
	Token tokens[TOKENS_MAX];
	lex_source(src, TOKENS_MAX, tokens);

	printf("\nOutput tokens...\n");
	int i = 0;
	while(tokens[i].type != _TOKENS_END) {
		if(tokens[i].type == _IDENTIFIER) {
			printf("Token %i is type %i and value %s.\n", i, tokens[i].type, tokens[i].value.string);
		} else {
			printf("Token %i is type %i and value %u.\n", i, tokens[i].type, tokens[i].value.byte);
		}

		i++;
	}

	printf("\nCompilation complete.\n");
	return 0;
}
