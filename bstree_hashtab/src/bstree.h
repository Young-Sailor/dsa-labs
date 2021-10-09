#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

struct bstree {
    char *key;
    uint32_t value;
    
    struct bstree *left;
    struct bstree *right;
};

struct bstree *bstree_create(char *key, int value);

void bstree_add(struct bstree *tree, char *key, int value);

struct bstree *bstree_lookup(struct bstree *tree, char *key);

struct bstree *bstree_delete(struct bstree *tree, char *key);

struct bstree *bstree_delete_node(struct bstree *tree, struct bstree *node, struct bstree *parent);

void bstree_replace_node(struct bstree *parent, struct bstree *node, struct bstree *child);

struct bstree *bstree_min(struct bstree *tree);

struct bstree *bstree_max(struct bstree *tree);