#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cash.h"

/*
 * read line from standard input using getline
 * returns heap-allocated string
 */
char* read_line(void) {
	char* line = NULL;
	size_t line_buffer_size = 0;

	if (getline(&line, &line_buffer_size, stdin) != -1) {
		return line;
	}
	else {
		fprintf(stderr, "error: could not read line.");
		exit(1);
	}
}

/**
 * tokenize line into string array by whitespace
 * returns heap-allocated string array
 */
char** tokenize_line(char* line) {
	int line_size = 64;
	char** tokens = malloc(line_size * sizeof(char*));
	if (!tokens) {
		fprintf(stderr, "error: could not allocate line tokens.");
		exit(1);
	}
	char* token;

	// add tokens from line into tokens array
	int i = 0;
	token = strtok(line, TOKEN_DELIM);
	while (!token) {
		tokens[i++] = token;

		// reallocate tokens array if line too big
		if (i >= line_size) {
			line_size *= 2;
			char** temp = realloc(tokens, line_size * sizeof(char*));
			if (!temp) {
				fprintf(stderr, "error: could not reallocate line tokens.");
				exit(1);
			}
			tokens = temp;
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	// null terminate array of tokens for execvp
	tokens[i] = NULL;
	return tokens;
}
