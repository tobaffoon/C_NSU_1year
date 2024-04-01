#include "integerset.h"

MYDLL_API IntegerSet *CreateSet(int* src, int size){
    IntegerSet *res = init_hash(size);
    int push_state;
    for (int i = 0; i < size; i++) {
        push_state = hash_push(res, src[i]);
        if(push_state == DUPLICATE_ERR) return NULL;
    }
    return res;
}

MYDLL_API char IsInSet(IntegerSet *set, int x){
    if(set == 0) return 0;
    if(set -> size == 0) return 0;

    uint32_t hash = jenkins((uint8_t *)&x, sizeof(int)) % set->size;
    Hash_node *newNode = set->arr + hash;
    while(newNode -> next != NULL){
        newNode = newNode -> next;
        if(newNode -> value == x)   return 1;
    }
    return 0;
}