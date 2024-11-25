#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "file.h"
#include "lex.h"
#include "parse.h"

#define PATH_MAX 4096
#define SRC_MAX 8192

// Agenda
// - Marks and jumps
// ---
// - Conditional jumps
// ---
// - Any more operators?

int main(int argc, const char** argv) {
	// Error check: wrong number of arguments
	if(argc == 1) {
		printf("Expected an argument, and you gave none. Use \"cicero help\" for usage information.\n", argc - 1);
		return 1;
	}

	if(strcmp(argv[1], "help") == 0) {
		printf(
			"Cicero is low-level language which compiles to NASM assembly and is assembled and linked with the C standard library using GCC. Currently, it is only compiled in elf64 (64-bit UNIX/Linux compatible) format.\n"
			"\nUsage\n"
			"  cicero help:              Show this help text.\n"
			"  cicero <source>: Compiles the source file, outputting the final executable to \"out\" by default.\n"
			"\nCompilation flags. Include after \"cicero <source_file>\".\n"
			"  -o <out>: Specifies the output file path for the final executable.\n"
			"  -r:       Runs the executable after successful compilation.\n"
			"  -asm:     Also outputs <out_filename>.asm after successful compilation containing the intermediary assembly code.\n"
			"  -obj:     Also outputs <out_filename>.o object file after successful compilation.\n"
		);
		return 0;
	}

	char source_path[PATH_MAX];
	strcpy(source_path, argv[1]);

	char out_path[PATH_MAX];
	strcpy(out_path, "out");

	bool flag_run = false;
	bool flag_obj = false;
	bool flag_asm = false;

	for(int argi = 2; argi < argc; argi++) {
		if(strcmp(argv[argi], "-o") == 0) {
			if(argc <= argi + 1) {
				printf("Expected a source filename after \"-o\" compilation flag.\n");
				return 1;
			}
			argi++;
			strcpy(out_path, argv[argi]);
		} else if(strcmp(argv[argi], "-r") == 0) {
			flag_run = true;
		} else if(strcmp(argv[argi], "-asm") == 0) {
			flag_asm = true;
		} else if(strcmp(argv[argi], "-obj") == 0) {
			flag_obj = true;
		} else {
			printf("Argument \"%s\" not recognized. Use \"cicero help\" for usage information.\n", argv[argi]);
			return 1;
		}
	}

	printf("Compiling...\n");

	// Read file
	char src[SRC_MAX];
	file_to_string(argv[1], SRC_MAX, src);

	// Perform lexical analysis
	Token tokens[TOKENS_MAX];
	lex(src, tokens);

	// Parse and output .asm file
	parse_and_compile(tokens, out_path);

	// Assemble
	printf("\nAssembling to executable...\n");

	char system_string[PATH_MAX + 512];

	sprintf(system_string, "nasm %s.asm -f elf64 -o %s.o", out_path, out_path);
	system(system_string);
	if(!flag_asm) {
		sprintf(system_string, "rm %s.asm", out_path);
		system(system_string);
	}

	sprintf(system_string, "gcc %s.o -no-pie -o %s", out_path, out_path);
	system(system_string);
	if(!flag_obj) {
		sprintf(system_string, "rm %s.o", out_path);
		system(system_string);
	}

	printf("Assembly complete.\n\n");

	if(!flag_run) {
		printf("Compilation complete. Executable at \"%s\"\n", out_path);
	} else {
		printf("Running executable at %s.\n", out_path);
		sprintf(system_string, "./%s", out_path);
		system(system_string);
	}

	return 0;
}
