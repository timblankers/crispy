#include <stdio.h>

void hello(int n) {
    printf("\nPrinting %d times:\n", n);
    for (int i=0; i<n; i++) {
        printf("%d: Hello World!\n", i);
    }
}

int main(int argc, char** argv) {
    printf("for loop\n");
    for (int i=0; i<5; i++) {
        printf("%d: Hello World!\n", i); 
    }

    printf("\nwhile loop\n");
    int x = 0;
    while (x<5) {
        printf("%d: Hello World!\n", x);
        x++;
    }

    hello(3);

    return 0;
}
