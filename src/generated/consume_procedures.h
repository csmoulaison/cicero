#pragma once

#define CONSUME_PROCEDURES_LEN 5

// const char* src, const uint32_t src_index
static ConsumeTokenRes consume_procedures(const char*, const uint32_t)[CONSUME_PROCEDURES_LEN] = {
	consume_statement_end,
	consume_keyword,
	consume_operator,
	consume_int_literal,
	consume_identifier
}
