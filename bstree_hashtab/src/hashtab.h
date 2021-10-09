#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE 128

struct listnode
{
    char *key;
    uint32_t value;

    struct listnode *next;
};

struct listnode *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(char *key);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, int value);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);
unsigned int AddHash(char *s);
unsigned int KRHash(char *s);
unsigned int ELFHash(char *s);
unsigned int JenkinsHash(char *s);