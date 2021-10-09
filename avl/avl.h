#pragma once

typedef struct Avltree {
    int key;
    char* value;

    int height;
    struct Avltree* left;
    struct Avltree* right;
} Avltree;

Avltree* avltree_create(int key, char* value);
Avltree* avltree_lookup(Avltree* root, int key);
void avltree_free(Avltree* root);
int avltree_height(Avltree* tree);
int avltree_balance(Avltree* tree);
Avltree* avltree_right_rotate(Avltree* tree);
Avltree* avltree_left_rotate(Avltree* tree);
Avltree* avltree_leftright_rotate(Avltree* tree);
Avltree* avltree_rightleft_rotate(Avltree* tree);
Avltree* avltree_add(Avltree* root, int key, char* value);
Avltree* avltree_min(Avltree* root);
Avltree* avltree_max(Avltree* root);
Avltree* avltree_delete(Avltree* root, int key);
void avltree_print(Avltree* root);