#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cash.h"

int main(void) {

	if (!isatty(STDIN_FILENO)) {
		fprintf(stderr, "error: invalid input source for shell.\n");
		return 1;
	}

	char* prompt = "$> ";
	char* line;
	char** argv;

	bool isRunning = true;
	while (isRunning) {
		printf("%s", prompt);
		line = read_line();
		argv = tokenize_line(line);
		// isRunning = execute(argv);
		free(line);
		free(argv);
	}

	return 0;
}
