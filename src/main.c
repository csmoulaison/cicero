#include <stdio.h>
#include "file.h"
#include "lex.h"
#include "parse.h"

#define SRC_MAX 8192

// Agenda
// - Marks and jumps
// ---
// - Conditional jumps
// ---
// - Any more operators?

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
	lex(src, tokens);

	parse_and_compile(tokens);

	// Assemble
	printf("\nAssembling to executable...\n");
	system("nasm program.asm -f elf64 -o program.o");
	system("gcc program.o -no-pie -o program");
	printf("Assembly complete.\n");

	printf("\nCompilation complete. Executable at \"%s\"\n", EXE_PATH);
	return 0;
}
