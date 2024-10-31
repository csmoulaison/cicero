#include "file.h"

void file_to_string(const char* path, const uint32_t buf_len, char* out_str) {
	FILE* file;
	file = fopen(path, "r");
	if(file == NULL) {
		printf("Error: File '%s' could not be read. Does it exist?\n", path);
		exit(1);
	}

	char c;
	uint32_t i = 0;
	while((c = fgetc(file)) != EOF) {
		if(i >= buf_len) {
			printf("Error: File contents are larger than the buffer length, which is %i.\n", buf_len);
			exit(1);
		}
		
		out_str[i] = c;
		i++;
	}

	out_str[i] = '\0';
	fclose(file);
}
