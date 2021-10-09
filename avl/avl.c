#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

Avltree* avltree_create(int key, char* value)
{
    Avltree* node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;

}

Avltree* avltree_lookup(Avltree* root, int key)
{
    while (root != NULL) {
        if (key == root->key) {
            return root;
        } else if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

void avltree_free(Avltree* root)
{
    if (root == NULL) {
        return;
    }
    avltree_free(root->left);
    avltree_free(root->right);
    free(root);
}

int avltree_height(Avltree* tree)
{
    if (tree != NULL) {
        return tree->height;
    } else {
        return -1;
    }
}

int avltree_balance(Avltree* tree)
{
    return avltree_height(tree->left) - avltree_height(tree->right);
}

int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

Avltree* avltree_right_rotate(Avltree* tree)
{
    Avltree* left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;

    tree->height = max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    left->height = max(avltree_height(left->left), tree->height) + 1;
    return left;
}

Avltree* avltree_left_rotate(Avltree* tree)
{
    Avltree* right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;

    tree->height = max(avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = max(avltree_height(right->right), tree->height) + 1;
    return right;
}

Avltree* avltree_leftright_rotate(Avltree* tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

Avltree* avltree_rightleft_rotate(Avltree* tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

Avltree* avltree_add(Avltree* root, int key, char* value)
{
    if (root == NULL) {
        return avltree_create(key, value);
    }
    if (key < root->key) {
        root->left = avltree_add(root->left, key, value);
        if (avltree_height(root->left) - avltree_height(root->right) == 2) {
            if (key < root->left->key) {
                root = avltree_right_rotate(root);
            } else {
                root = avltree_leftright_rotate(root);
            }
        }
    } else if (key > root->key) {
        root->right = avltree_add(root->right, key, value);
        if (avltree_height(root->right) - avltree_height(root->left) == 2) {
            if (key > root->right->key) {
                root = avltree_left_rotate(root);
            } else {
                root = avltree_rightleft_rotate(root);
            }
        }
    }
    root->height = max(avltree_height(root->left), avltree_height(root->right)) + 1;
    return root;
}

Avltree* avltree_min(Avltree* root)
{
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Avltree* avltree_max(Avltree* root)
{
    if (root == NULL) {
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

Avltree* avltree_delete(Avltree* root, int key)
{
    // Если удаляемый ключ меньше
    // чем корневой ключ, то он лежит
    // в левом поддерев
    if (key < root->key) {
        root->left = avltree_delete(root->left, key);
    // Если удаляемый ключ больше
    // чем корневой ключ, то он лежит
    // в правом поддереве
    } else if (key > root->key) {
        root->right = avltree_delete(root->right, key);
    // если ключ такой же, как и ключ root узла, то
    // это узел, который нужно удалить
    } else {
        // узел только с одним потомком или без потомка
        if ((root->left == NULL) || (root->right == NULL)) {
            Avltree* temp;
            if (root->left != NULL) {
                temp = root->left;
            } else {
                temp = root->right;
            }
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {           // One child case
                *root = *temp; // copy the contents of the non-empty child
            }
            free(temp);
        } else {
            // узел с двумя дочерними элементами: получаем преемника по порядку (наименьшего в правом поддереве)
            Avltree* temp = avltree_min(root->right);
            // Копируем данные преемника в этот узел
            root->key = temp->key;
            // Удаляем преемника в порядке
            root->right = avltree_delete(root->right, temp->key);
        }
    }
    // Если в дереве был только один узел, то возвращаем его
    if (root == NULL) {
        return root;
    }
    // обновляем высоту текущего узла
    root->height = 1 + max(avltree_height(root->left), avltree_height(root->right));
    // получаем balance factor текущего узла, чтобы проверить, не стал ли этот узел неуравновешенным
    int balance = avltree_balance(root);
    // Если узел несбалансирован, то используем повороты в зависимости от ситуации
    if (balance > 1 && avltree_balance(root->left) >= 0) {
        return avltree_right_rotate(root);
    }
    if (balance > 1 && avltree_balance(root->left) < 0) {
        return avltree_leftright_rotate(root);
    }
    if (balance < -1 && avltree_balance(root->right) <= 0) {
        return avltree_left_rotate(root);
    }
    if (balance < -1 && avltree_balance(root->right) > 0) {
        return avltree_rightleft_rotate(root);
    }
    return root;
}

void avltree_print(Avltree* root)
{
    if (root != NULL) {
        printf("%d %s\n", root->key, root->value);
        avltree_print(root->left);
        avltree_print(root->right);
    }
}