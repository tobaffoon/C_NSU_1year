#include "hash_table.h"

uint32_t jenkins(const uint8_t *key, size_t len){
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i){
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int hash_push(Hash_table* table, int n){
    uint32_t hash = jenkins((uint8_t *)&n, sizeof(int)) % table->size;
    Hash_node *newNode = table->arr + hash;
    while(newNode -> next != NULL){
        newNode = newNode -> next;
        if(newNode -> value == n)   return DUPLICATE_ERR;
    }

    newNode -> next = malloc(sizeof(Hash_node));
    newNode = newNode -> next;
    newNode -> value = n;
    newNode -> next = NULL;

    return SUCCESSFUL_PUSH;
}

Hash_table* init_hash(int length){
    Hash_table *table = malloc(sizeof(Hash_table));
    table -> arr = calloc(length * 2, sizeof(Hash_node));
    table -> size = length * 2;
    return table;
}