#include <stdio.h>
#include <stdlib.h>

/* Windows only functions */
#ifdef _WIN32

/* If not Windows, include the editline headers */
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {

	printf("Lispy Version 0.0.0.0.1\n");
	printf("Press Ctrl+c to Exit\n");

	while (1) {
		char* input = readline("lispy> ");
		add_history(input);
		printf("No you're a %s\n", input);
		free(input);
	}
	return 0;
}