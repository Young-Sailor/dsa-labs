#include "skiplist.h"

#include <stdio.h>

static void skiplist_dump(SkipList *list)
{
    Node *x = list->header;
    while (x && x->forward[1] != list->header)
    {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NIL\n");
}

int main()
{
    int arr[] = {3, 6, 9, 2, 11, 1, 4}, i;
    SkipList list;
    skiplist_init(&list);

    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        skiplist_insert(&list, arr[i], arr[i]);
    }
    skiplist_dump(&list);

    printf("Search:--------------------\n");
    int keys[] = {3, 4, 7, 10, 111};

    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        Node *x = skiplist_search(&list, keys[i]);
        if (x)
        {
            printf("key = %d, value = %d\n", keys[i], x->value);
        }
        else
        {
            printf("key = %d, not found\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    skiplist_delete(&list, 3);
    skiplist_delete(&list, 9);
    skiplist_dump(&list);

    return 0;
}