#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <string.h>

#define IN_BUF_LEN 256

void run(const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        if(src[i] == ' ') {
            printf("\n");
        } else {
            printf("%c", src[i]);
        }
        i++;
    }
}

int run_interactive_interpreter() {
    char in_buf[IN_BUF_LEN];

    for(;;) {
        printf("> ");
        fgets(in_buf, IN_BUF_LEN, stdin);
        if(strlen(in_buf) < 1) {
            break;
        }
        run(in_buf);
    }

    return 0;
}

int run_file_interpreter(const char* path) {
    FILE *file = fopen(path, "r");
    if(file == NULL) {
        printf("File '%s' cannot be opened. Does it exist?", path);
        return 1;
    }

    char src_buf[4096];
    int c = 0;
    int i = 0;
    while((c = fgetc(file)) != EOF) {
        src_buf[i++] = (char)c;
    }
    src_buf[i] = '\0';

    run(src_buf);

    return 0;
}

#endif
