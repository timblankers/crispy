#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

/* Windows only functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Readline function replacement */
char* readline(char* prompt) {
	fputs(prompt, stdout);					// output prompt
	fgets(buffer, 2048, stdin);				// receive command
	char* cpy = malloc(strlen(buffer)+1);	// allocate space for copy of command
	strcpy(cpy, buffer);					// copy command
	cpy[strlen(cpy)-1] = '\0';				// add string terminator
	return cpy;
}

/* add_history function replacement */
void add_history(char* unused) {}

/* If not Windows, include the editline headers */
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {

	printf("Lispy Version 0.0.0.0.3\n");
	printf("Author: Tim Blankers with a noisy rooster\n");
	printf("Press Ctrl+c to Exit\n");

	while (1) {
		char* input = readline("toktok> ");
		add_history(input);
		printf("No you're a %s TOOOK!\n", input);
		free(input);
	}
	return 0;
}