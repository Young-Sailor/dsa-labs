#include <bstree.h>
#include <hashtab.h>
#include <somefuncs.h>
#include <stdlib.h>

#define SIZE 200000

void hashtab_exp(char **words)
{
    int i, j;
    struct listnode *node;

    printf("Hash Table:\n");
    hashtab_init(hashtab);
    for (i = 1; i <= SIZE; ++i) {
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0) {
            double avr_time = 0;
            for (j = 0; j < 10; ++j) {
                char *w = words[getrand(0, i - 1)];
                double t = wtime();
                node = hashtab_lookup(hashtab, w);
                t = wtime() - t;
                avr_time += t;
                if (node != NULL) {
                    // printf("n = %d; time = %lf\n", i, t);
                }
            }
            printf("    n = %d; time = %.6lf\n\n", i, avr(avr_time));
        }
    }
    printf("\n");
}

void bstree_exp(char **words)
{
    int i, j;
    struct bstree *tree = bstree_create(words[0], 0);
    struct bstree *node;

    printf("Binary Search Tree:\n");
    for (i = 2; i <= SIZE; ++i) {
        bstree_add(tree, words[i - 1], i - 1);
        if (i % 10000 == 0) {
            double avr_time = 0;
            for (j = 0; j < 10; ++j) {
                char *w = words[getrand(0, i - 1)];
                double t = wtime();
                node = bstree_lookup(tree, w);
                t = wtime() - t;
                avr_time += t;
                if (node != NULL) {
                    // printf("n = %d; time = %lf\n", i, t);
                }
            }
        printf("    n = %d; time = %.6lf\n\n", i, avr(avr_time));
        }
    }
    printf("\n");
}

int main()
{
    char *words[SIZE];
    load_some_words(words);

    printf("~Starting the experiment~\n");
    hashtab_exp(words);
    bstree_exp(words);

    //free(words);
    return 0;
}