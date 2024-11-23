#include <stdio.h>
#include "file.h"
#include "lex.h"
#include "parse.h"

#define SRC_MAX 8192

// Agenda
// - Global variables
// - Arithmetic on variables
// ---
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

	int i = 0;
	while(tokens[i].type != TOKEN_PROGRAM_END) {
		printf("%i\n", tokens[i].type);
		i++;
	}

	parse_and_compile(tokens);

	// Assemble
	printf("\nAssembling to executable...\n");
	system("nasm -f elf64 program.asm -o program.o");
	//system("rm program.asm");
	system("ld -m elf_x86_64 program.o -o program");
	system("rm program.o");
	printf("Assembly complete.\n");

	printf("\nCompilation complete. Executable at \"%s\"\n", EXE_PATH);
	return 0;
}
