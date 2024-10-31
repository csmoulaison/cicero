#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void file_to_string(const char* path, const uint32_t buf_len, char* out_str);
