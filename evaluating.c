#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int most_children(mpc_ast_t* t) {
	if (t->children == 0) {
		return 0;
	}
	int highest = t->children_num;
	for (int i=0; i<t->children_num; i++) {
		int n_children = most_children(t->children[i]);
		if (n_children > highest) {
			highest = n_children;
		}
	}
	return highest;
}

int n_branches(mpc_ast_t* t) {
	if (t->children_num == 0) {
		return 0;
	} else {
		int branches = t->children_num;
		for (int i=0; i<t->children_num; i++) {
			branches += n_branches(t->children[i]);
		}
		return branches;
	}
}

int n_leaves(mpc_ast_t* t) {
	if (t->children_num == 0) {
		return 1;
	} else {
		int leaves = 0;
		for (int i=0; i<t->children_num; i++) {
			leaves += n_leaves(t->children[i]);
		}
		return leaves;
	}
}

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  if (strcmp(op, "%") == 0) { return x % y; }
  if (strcmp(op, "^") == 0) { return pow(x,y); }
  return 0;
}

long eval(mpc_ast_t* t) {
  
  /* If tagged as number return it directly. */ 
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }
  
  /* The operator is always second child. */
  char* op = t->children[1]->contents;
  
  /* We store the third child in `x` */
  long x = eval(t->children[2]);
  
  /* Iterate the remaining children and combining. */
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  
  return x;  
}

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
	    operator : '+' | '-' | '*' | '/' | '%' | '^' | /add/ | /sub/ | /mul/ | /div/;    \
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
		  /* On Success Print the evaluation */
		  long result = eval(r.output);
		  printf("Answer: %li\n", result);
		  printf("Leaves: %d\n", n_leaves(r.output));
		  printf("Branches: %d\n", n_branches(r.output));
		  printf("Most Children: %d\n", most_children(r.output));
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