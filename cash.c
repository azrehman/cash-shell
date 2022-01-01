#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
		fprintf(stderr, "error: could not read line.\n");
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
		fprintf(stderr, "error: could not allocate line tokens.\n");
		exit(1);
	}
	char* token;

	// add tokens from line into tokens array
	int i = 0;
	token = strtok(line, TOKEN_DELIM);
	while (token != NULL) {
		tokens[i++] = token;

		// reallocate tokens array if line too big
		if (i >= line_size) {
			line_size *= 2;
			char** temp = realloc(tokens, line_size * sizeof(char*));
			if (!temp) {
				fprintf(stderr, "error: could not reallocate line tokens.\n");
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


/**
 * creates child process and executes command from argv
 * returns true if successful
 */
bool launch(char** argv) {
	pid_t pid = fork();
	if (pid == 0) {
		// child process
		// execute command
		if (execvp(argv[0], argv) == -1) {
			fprintf(stderr, "error: could not execute command.\n");
		}
		return false;
	}
	else if (pid == -1) {
		// error shell
		fprintf(stderr, "error: could not fork parent.\n");
		exit(1);
	}
	else {
		// parent process
		// wait for child process to finish
		wait(NULL);
	}
	return true;
}

/*
 * array of built-in function pointers
 * each function takes a string array argument
 * return value indicates if shell keeps executing
 */
bool (*builtin_func_ptr[])(char**) = {
	&shell_cd, &shell_help, &shell_exit
};

/**
 * executes shell built-ins and other programs
 * returns true if shell keeps prompting for input
 * returns false if shell should exit
 */
bool execute(char** argv) {
	// exit if argv is somehow null
	if (!argv) {
		return false;
	}
	// return true on empty command
	if (argv[0] == NULL) {
		return  true;
	}

	// check if command is a shell built-in
	for (size_t i = 0; i < 3; ++i) {
		if (!strcmp(argv[0], BUILTIN_FUNC_NAMES[i])) {
			return (*builtin_func_ptr[i])(argv);
		}
	}

	// else execute by forking and using execvp
	return launch(argv);
}

// ~~~~~~~~~~~~~~~~~~~~ SHELL BUILT-IN COMMANDS ~~~~~~~~~~~~~~~~~~~~


/**
 * changes current working directory of shell
 */
bool shell_cd(char** argv) {
	// if no argument for cd, then cd to homde dir
	if (argv[1] == NULL) {
		fprintf(stderr, "cd error: missing directory argument\n");
	}
	else {
		if (chdir(argv[1]) != 0) {
			fprintf(stderr, "cd error: invalid directory \"%s\"\n", argv[1]);

		}
	}
	return true;
}

/**
 * prints shell help message
 */
bool shell_help(char** argv) {
	fprintf(stdout, "Cash Shell\n");
	return true;
}

/**
 * exits the shell
 */
bool shell_exit(char** argv) {
	return false;
}

