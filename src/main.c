#include <stdio.h>
#include "interpreter.h"

int main(int argc, char **argv) {
    if(argc > 2) {
        printf("Too many arguments. Expected 1.\n");
        printf("Usage:\n");
        printf("  cicero: start the interactive interpreter.\n");
        printf("  cicero <script>: run a script file.\n");
        return 1;
    }

    if(argc == 1) {
        return run_interactive_interpreter();
    }

    return run_file_interpreter(argv[1]);
    return 0;
}
