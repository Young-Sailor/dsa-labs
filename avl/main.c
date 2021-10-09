#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "avl.h"

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

int main()
{
    srand(time(0));
    Avltree* tree;
    char words[50000][32];
    FILE* file_handle = fopen("words.txt", "rt");
    if (file_handle == NULL) {
        printf("Can't open the file with words\n");
        return -1;
    }
    for (int i = 0; i < 50000; ++i) {
        fscanf(file_handle, "%31s", words[i]);
    }
    /* для подтверждения лог. зависимости
    tree = avltree_create(0, words[0]);
    for (int i = 1; i < 50000; ++i) {
        tree = avltree_add(tree, i, words[i]);
    }
    double t = wtime();
    Avltree* sought = avltree_lookup(tree, getrand(0, 50000));
    t = wtime() - t;
    printf("time: %lf\nsought: %d %s\n", t, sought->key, sought->value);
    */
    int k = rand() % 50000;
    tree = avltree_create(k, words[k]);
    for (int i = 1; i < 8; ++i) {
        k = rand() % 50000;
        tree = avltree_add(tree, k, words[k]);
    }
    avltree_print(tree);

    printf("\nTry to remove max and min elems: \n\n");
    Avltree* max_elem = avltree_max(tree);
    Avltree* min_elem = avltree_min(tree);
    tree = avltree_delete(tree, max_elem->key);
    tree = avltree_delete(tree, min_elem->key);
    avltree_print(tree);

    printf("\nTry to add new elem: \n\n");
    k = rand() % 50000;
    Avltree* new_elem = avltree_lookup(tree, k);
    while (new_elem != NULL) {
        k = rand() % 50000;
        new_elem = avltree_lookup(tree, k);
    }
    tree = avltree_add(tree, k, "new");
    avltree_print(tree);

    fclose(file_handle);
    avltree_free(tree);
    return 0;
}