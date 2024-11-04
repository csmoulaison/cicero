
while(loopin) {
	ConsumeTokenRes res;

	res = consume_keyword(src);
	if(res.success) {
		goto found_matching_token;
	}

	res = consume_newline(src);
	if((res = consume_keyword(src))) {
		goto found_matching_token) {
	}

	if(!res.success) {
		continue;
	}

found_matching_token:
	src_index += res.chars_read;
}
