#include <stdint.h>
#include <stdlib.h>
#ifndef _HASH_TABLE_
#define _HASH_TABLE_
#define DUPLICATE_ERR (-1)
#define SUCCESSFUL_PUSH 1
uint32_t jenkins(const uint8_t *key, size_t len);

typedef struct Hash_node{
    int value;
    struct Hash_node *next;
}Hash_node;

typedef struct Hash_table{
    Hash_node *arr;
    int size;
} Hash_table;

int hash_push(Hash_table* table, int n);

Hash_table* init_hash(int length);
#endif