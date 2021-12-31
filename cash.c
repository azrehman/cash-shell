#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char* read_line(void);
int main() {

	if (!isatty(STDIN_FILENO)) {
		fprintf(stderr, "error: invalid input source for shell.\n");
		return 1;
	}

	char* prompt = "$> ";
	char* line;
	char** argv = malloc(10 * sizeof(char*));

	bool isRunning = true;
	while (isRunning) {
		printf("%s", prompt);
		line = read_line();
		// argv = tokenize_line(line);
		// isRunning = execute(argv);
	}

	return 0;
}

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


