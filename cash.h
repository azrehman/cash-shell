#pragma once

#include <stdbool.h>

// characters which can deliminate line into tokens in shell
static const char TOKEN_DELIM[] = " \t\n\r\a";

/*
 * read line from standard input using getline
 * returns heap-allocated string
 */
char* read_line(void);

/**
 * tokenize line into string array by whitespace
 * returns heap-allocated string array
 */
char** tokenize_line(char* line);

/**
 * creates child process and executes command from argv
 * returns true if successful
 */
bool launch(char** argv);


/**
 * executes shell built-ins and other programs
 * returns true if shell keeps prompting for input
 * returns false if shell should exit
 */
bool execute(char** argv);


// ~~~~~~~~~~~~~~~~~~~~ SHELL BUILT-IN COMMANDS ~~~~~~~~~~~~~~~~~~~~

// array of built-in commands
static const char* BUILTIN_FUNC_NAMES[] = {
	"cd", "help", "exit"
};

/**
 * changes current working directory of shell
 */
bool shell_cd(char** argv);

/**
 * prints shell help message
 */
bool shell_help(char** argv);

/**
 * exits the shell
 */
bool shell_exit(char** argv);


