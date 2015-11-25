#include <stdio.h>
#include <string.h>

typedef struct Movies {
    char title[50];
    char director[50];
    char imdb[50];
    short stars;
    short release_date;
} Movie;

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

    int y = 2;

    switch(y) {
        case 0:
            printf("It's zero\n");
            break;
        case 1:
            printf("It's one\n");
            break;
        case 2:
            printf("It's two\n");
            break;
        default:
            printf("I have no idea\n");
    }

    Movie sample;
    strcpy(sample.title, "Star Wars");
    strcpy(sample.director, "George Lucas");
    strcpy(sample.imdb, "http://www.imdb.com/title/tt0076759/");
    sample.stars = 4;
    sample.release_date = 2510;

    printf("Director: %s\n", sample.director);


    return 0;
}
