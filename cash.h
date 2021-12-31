#pragma once

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
