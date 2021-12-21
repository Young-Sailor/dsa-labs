#include "skiplist.h"

#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define SKIPLIST_MAX_LEVEL 6

SkipList *skiplist_init(SkipList *list)
{
    int i;
    Node *header = malloc(sizeof(struct Node));
    list->header = header;
    header->key = INT_MAX;
    header->forward = malloc(sizeof(Node *) * (SKIPLIST_MAX_LEVEL + 1));
    for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++)
    {
        header->forward[i] = list->header;
    }

    list->level = 1;
    list->size = 0;

    return list;
}

static int rand_level()
{
    srand(time(0));
    int level = 1;
    float r = rand() / RAND_MAX;
    // while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
    while ((r < 0.5) && (level < SKIPLIST_MAX_LEVEL))
    {
        ++level;
    }
    return level;
}

int skiplist_insert(SkipList *list, int key, int value)
{
    Node *update[SKIPLIST_MAX_LEVEL + 1];
    Node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--)
    {
        while (x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[1];

    if (key == x->key)
    {
        x->value = value;
        return 0;
    }
    else
    {
        level = rand_level();
        if (level > list->level)
        {
            for (i = list->level + 1; i <= level; i++)
            {
                update[i] = list->header;
            }
            list->level = level;
        }

        x = malloc(sizeof(Node));
        x->key = key;
        x->value = value;
        x->forward = malloc(sizeof(Node *) * (level + 1));
        for (i = 1; i <= level; i++)
        {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}

Node *skiplist_search(SkipList *list, int key)
{
    Node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--)
    {
        while (x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
    }
    if (x->forward[1]->key == key)
    {
        return x->forward[1];
    }
    else
    {
        return NULL;
    }
    return NULL;
}

static void skiplist_node_free(Node *x)
{
    if (x)
    {
        free(x->forward);
        free(x);
    }
}

int skiplist_delete(SkipList *list, int key)
{
    int i;
    Node *update[SKIPLIST_MAX_LEVEL + 1];
    Node *x = list->header;
    for (i = list->level; i >= 1; i--)
    {
        while (x->forward[i]->key < key)
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key)
    {
        for (i = 1; i <= list->level; i++)
        {
            if (update[i]->forward[i] != x)
            {
                break;
            }
            update[i]->forward[1] = x->forward[i];
        }
        skiplist_node_free(x);

        while (list->level > 1 && list->header->forward[list->level] == list->header)
        {
            list->level--;
        }
        return 0;
    }
    return 1;
}