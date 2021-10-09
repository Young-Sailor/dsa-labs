#include <somefuncs.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void load_some_words(char **words)
{
    int i;
    FILE *loader = fopen("scripts/words.txt", "r");
    if (loader == NULL) {
        printf("Can't load some words...\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < SIZE; ++i) {
        words[i] = malloc(30);
        if (words[i] == NULL) {
            printf("Can't allocate some memory =(\n");
            free(words);
            exit(EXIT_FAILURE);
        }
        fscanf(loader, "%s", words[i]);
    }
    fclose(loader);
}

double avr(double average_time)
{
    return (double)average_time / 9;
}