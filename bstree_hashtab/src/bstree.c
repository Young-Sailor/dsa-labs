#include <bstree.h>

struct bstree *bstree_create(char *key, int value)
{
    struct bstree *node;

    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
struct bstree *bstree_lookup(struct bstree *tree, char *key)
{
    while (tree != NULL) {
        if (key == tree->key) {
            return tree;
        } else if (key < tree->key) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return tree;
}

void bstree_add(struct bstree *tree, char *key, int value)
{
    if (tree == NULL) {
        return;
    }
    struct bstree *parent, *node;
    while (tree != NULL) {
        parent = tree;
        if (key < tree->key) {
            tree = tree->left;
        } else if (key > tree->key) {
            tree = tree->right;
        } else {
            return;
        }
    }
    node = bstree_create(key, value);
    if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

struct bstree *bstree_delete(struct bstree *tree, char *key)
{
    struct bstree *parent;
    struct bstree *node = tree;
    while ((node != NULL) && (node->key != key)) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (node == NULL) {
        return tree;
    } else {
        return bstree_delete_node(tree, node, parent);
    }
}

struct bstree *bstree_delete_node(struct bstree *tree, struct bstree *node, struct bstree *parent)
{
    if (node->left == NULL) {
        bstree_replace_node(parent, node, node->right);
        if (parent == NULL) {
            tree = node->right;
        }
    } else if (node->right == NULL) {
        bstree_replace_node(parent, node, node->left);
        if (parent == NULL) {
            tree = node->left;
        }
    } else {
        struct bstree *min = node->right;
        struct bstree *minparent = min;
        while (min->left != NULL) {
            minparent = min;
            min = min->left;
        }
        bstree_replace_node(parent, node, min);
        if (parent == NULL) {
            tree = min;
        }
        if (node->right != min) {
            minparent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        } else {
            min->left = node->left;
        }
    }
    free(node);
    return tree;
}

void bstree_replace_node(struct bstree *parent, struct bstree *node, struct bstree *child)
{
    if (parent != NULL) {
        if (node->key < parent->key) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }
}

struct bstree *bstree_min(struct bstree *tree)
{
    if (tree == NULL) {
        return NULL;
    }

    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

struct bstree *bstree_max(struct bstree *tree)
{
    if (tree == NULL) {
        return NULL;
    }

    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}