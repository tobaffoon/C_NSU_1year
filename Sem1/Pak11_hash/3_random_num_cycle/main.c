#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define HASH_LENGTH 4000000     //because max value of right boarder is 2000000

//to make hash table more effective we use hash(idx) that is very different from state value, so we keep both of them
typedef struct Cell{
    uint64_t state_val;
    uint32_t idx;
} Cell;

typedef struct Node{
    Cell value;
    struct Node *next;
} Node;

typedef struct HashTable{
    uint32_t length;
    Node **head;
} HashTable;

uint32_t    jenkins             (const uint8_t *key, size_t len);
uint64_t    change_state        (uint64_t s, uint64_t a, uint64_t b, uint64_t c, uint64_t M);
void        find_func_cycle     (uint32_t *left, uint32_t *right, Node **list, uint32_t table_len, uint64_t a, uint64_t b, uint64_t c, uint64_t M);

uint32_t jenkins(const uint8_t *key, size_t len){
    uint32_t hash=0;
    for(int i = 0; i < len; i++){
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

uint64_t change_state(uint64_t s, uint64_t a, uint64_t b, uint64_t c, uint64_t M){
    return (s*s*a + s*b + c) % M;
}

void find_func_cycle(uint32_t *left, uint32_t *right, Node **list, uint32_t table_len, uint64_t a, uint64_t b, uint64_t c, uint64_t M){
    uint64_t state = 1;
    uint32_t hash = jenkins((const uint8_t*)&state, sizeof(uint64_t)) % table_len;

    list[hash] = calloc(1, sizeof(Node));
    list[hash] -> value.state_val = state;
    list[hash] -> value.idx = *left;
    (*left)++;

    state = change_state(state, a, b, c, M);
    hash = jenkins((const uint8_t*)&state, sizeof(uint64_t)) % table_len;

    //temp is used to traverse the list
    Node *temp;
    do {
        temp = list[hash];

        //if there were no value with this hash, we allocate memory for it
        if(temp == NULL){
            list[hash] = malloc(sizeof(Node));
            temp = list[hash];
        }

        else {
            //temp_prev is used to allocate memory for the last nod with this hash.
            //instead of adding temp_prev we could check if temp -> next is NULL, but it seems to take too long
            Node *temp_prev;
            while (temp != NULL) {
                //we don't have any condition for leaving external while cycle, because it seems easier to just look for equal states inside it.
                if (state == temp->value.state_val) {
                    *right = *left;
                    *left = temp->value.idx;
                    return;
                }

                temp_prev = temp;
                temp = temp->next;
            }
            temp_prev -> next = malloc(sizeof(Node));
            temp = temp_prev -> next;
        }

        //initialisation of new nod
        temp -> value.idx = *left;
        temp -> value.state_val = state;
        temp -> next = NULL;
        (*left)++;

        state = change_state(state, a, b, c, M);
        hash = jenkins((const uint8_t*)&state, sizeof(uint64_t)) % table_len;
    }while(1);
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    uint64_t    first_coef,
            sec_coef,
            third_coef,
            table_len;

    fscanf(fi, "%llu %llu %llu %llu", &table_len, &first_coef, &sec_coef, &third_coef);

    HashTable *hash_table = malloc(sizeof(HashTable));
    hash_table -> length = HASH_LENGTH;
    hash_table -> head = calloc(hash_table -> length, sizeof(Node *));

    uint32_t    l = 0,
                r = 0;

    //this function places the values we are looking for in l and r valuables
    find_func_cycle(&l, &r, hash_table->head, hash_table->length,first_coef, sec_coef, third_coef, table_len);

    fprintf(fo, "%u %u", l, r);
    fclose(fi);
    fclose(fo);
    return 0;
}