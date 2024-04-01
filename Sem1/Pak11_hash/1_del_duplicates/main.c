#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    uint32_t value;
    struct Node *next;
} Node;

typedef struct HashTable {
    uint32_t length;
    Node **head;
} HashTable;

uint32_t get_hash_table_len(uint32_t nun_of_elem);

uint32_t jenkins(const uint8_t *key, size_t len);

void add_hash(HashTable *htable, int32_t val, int32_t **result_arr, uint32_t *length);

uint32_t read_hash_list(HashTable *dest, uint32_t len, int32_t **result_arr, FILE *input);

//finds the closest power of two that is bigger than 175% of initial len
uint32_t get_hash_table_len(uint32_t nun_of_elem) {
    uint32_t comp = (nun_of_elem << 1) - (nun_of_elem >> 2);    //get 1.75 len
    uint32_t res = 0x00200000;      //it's 2^21, which is bigger than 1.75*1000000 (the max number of input integers)
    while ((res & comp) == 0) {
        res >>= 1;
    }
    return res << 1;
}

uint32_t jenkins(const uint8_t *key, size_t len) {
    uint32_t hash = 0;
    for (int i = 0; i < len; i++) {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

//adds val by its hash in table, also (if val is unique) puts it in result arr, and increases the overall length of result arr
void add_hash(HashTable *htable, int32_t val, int32_t **result_arr, uint32_t *length) {
    uint32_t key = jenkins((uint8_t *) &val, sizeof(val)) & (htable->length - 1);
    //length - 1 returns the mask that will give us remainder of division by power of two
    Node **table = htable->head;

    if (table[key] == NULL) {
        table[key] = malloc(sizeof(Node));
        table[key]->value = val;
        table[key]->next = NULL;
    } else {
        Node *temp = table[key];

        if (temp->value == val) return;
        while (temp->next != NULL) {
            if (temp->value == val) return;
            temp = temp->next;
        }
        if (temp->value == val) return;

        temp->next = malloc(sizeof(Node));
        temp = temp->next;

        temp->value = val;
        temp->next = NULL;
    }

    **result_arr = val;
    (*result_arr)++;

    (*length)++;
}

//reads len elements from input and saves them in dest (unorganized) and result_arr (in initial order)
uint32_t read_hash_list(HashTable *dest, uint32_t len, int32_t **result_arr, FILE *input) {
    uint32_t res = 0;
    for (int i = 0; i < len; i++) {
        int32_t current;
        fread(&current, sizeof(int32_t), 1, input);
        add_hash(dest, current, result_arr, &res);
    }
    return res;
}

int main() {
    FILE *fi = fopen("input.bin", "rb"),
            *fo = fopen("output.bin", "wb");

    uint32_t length,                 //number of numbers
    length_of_uniques;      //number of unique elements

    fread(&length, sizeof(length), 1, fi);

    HashTable *hash_l = calloc(1, sizeof(HashTable));
    hash_l->length = get_hash_table_len(length);
    hash_l->head = calloc(hash_l->length, sizeof(Node *));

    int32_t *unique_elems = malloc(length * sizeof(int32_t));           //array that lets us remember the order of elements
    length_of_uniques = read_hash_list(hash_l, length, &unique_elems, fi);

    unique_elems -= length_of_uniques;      //we moved pointer to the first elem of this array in our read function

    fwrite(&length_of_uniques, sizeof(uint32_t), 1, fo);
    fwrite(unique_elems, sizeof(uint32_t), length_of_uniques, fo);

    free(hash_l);
    free(unique_elems);
    fclose(fi);
    fclose(fo);
    return 0;
}
