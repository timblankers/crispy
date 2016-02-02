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

	/* Create Some Parsers */
	mpc_parser_t* Number   = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr     = mpc_new("expr");
	mpc_parser_t* Crispy    = mpc_new("crispy");

	/* Define them with the following Language */
	mpca_lang(MPCA_LANG_DEFAULT,
	  "                                                     \
	    number   : /-?[0-9]+([.][0-9]+)?/ ;                             \
	    operator : '+' | '-' | '*' | '/' | '%' | /add/ | /sub/ | /mul/ | /div/;    \
	    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
	    crispy    : /^/ <operator> <expr>+ /$/ ;             \
	  ",
	  Number, Operator, Expr, Crispy);

	printf("Crispy Version 0.0.0.0.3\n");
	printf("Author: Tim Blankers with a noisy rooster\n");
	printf("Press Ctrl+c to Exit\n");

	while (1) {
		char* input = readline("toktok> ");
		add_history(input);

		/* Attempt to Parse the user Input */
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Crispy, &r)) {
		  /* On Success Print the AST */
		  mpc_ast_print(r.output);
		  mpc_ast_delete(r.output);
		} else {
		  /* Otherwise Print the Error */
		  mpc_err_print(r.error);
		  mpc_err_delete(r.error);
		}

		free(input);
	}

	/* Undefine and Delete our Parsers */
	mpc_cleanup(4, Number, Operator, Expr, Crispy);

	return 0;
}