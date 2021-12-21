#pragma once

typedef struct Node
{
    int key;
    int value;
    struct Node **forward;
} Node;

typedef struct SkipList
{
    int level;
    int size;
    struct Node *header;
} SkipList;

SkipList *skiplist_init(SkipList *list);
int skiplist_insert(SkipList *list, int key, int value);
Node *skiplist_search(SkipList *list, int key);
int skiplist_delete(SkipList *list, int key);