#include <hashtab.h>

unsigned int hashtab_hash(char *key)
{
    unsigned int h = 0, hash_mul = 31;

    while (*key) {
        h = h * hash_mul + (unsigned int)*key++;
    }
    return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab)
{
    int i;

    for (i = 0; i < HASHTAB_SIZE; i++) {
        hashtab[i] = NULL;
    }
}

void hashtab_add(struct listnode **hashtab, char *key, int value)
{
    struct listnode *node;

    int index = hashtab_hash(key);
    node = malloc(sizeof(*node));
    if (node != NULL) {
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
    struct listnode *node;

    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            return node;
        }
    }
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key)
{
    struct listnode *node, *prev = NULL;
    int index = hashtab_hash(key);
    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (0 == strcmp(node->key, key)) {
            if (prev == NULL) {
                hashtab[index] = node->next;
            } else {
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
}

// There are several other hash functions:

unsigned int AddHash(char *s)
{
    unsigned int h = 0;
    while (*s) {
        h += (unsigned int)*s++;
    }
    return h % HASHTAB_SIZE;
}

unsigned int KRHash(char *s)
{
    unsigned int h = 0, hash_mul = 31;
    while (*s) {
        h = h * hash_mul + (unsigned int)*s++;
    }
    return h % HASHTAB_SIZE;
}

unsigned int ELFHash(char *s)
{
    unsigned int h = 0, g;
    while (*s) {
        h = (h << 4) + (unsigned int)*s++;
        g = h & 0xF0000000L;
        if (g) {
            h ^= g >> 24;
        }
    h &= ~g;
    }
    return h % HASHTAB_SIZE;
}

unsigned int JenkinsHash(char *s)
{
    unsigned int h = 0;
    while (*s) {
        h += (unsigned int)*s++;
        h += (h << 10);
        h ^= (h >> 6);
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h % HASHTAB_SIZE;
}