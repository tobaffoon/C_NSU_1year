#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct TBinTree{
    int val,
        count;
    struct TBinTree *l,
                    *r;
} BinaryTree;

uint32_t    jenkins             (const uint8_t *key, size_t len);
void        swap                (int *a, int *b);
void        shuffle_array       (int* arr, int len);
void        add_to_bintree      (BinaryTree *tree, int new_val);
void        fill_bintree        (BinaryTree *dest, const int* src, int num_of_elems);
void        print_bintree       (BinaryTree *tree, FILE *output);

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

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//uses jenkins hash-function to swap random elements in array
void shuffle_array(int* arr, int len){
    uint32_t random = len - 1;
    for (int i = 0; i < len; i++) {
        random = jenkins((uint8_t *)&random, sizeof(uint32_t)) % len;
        swap(arr + i, arr + random);
    }
}

//adds new leaf to bintree
void add_to_bintree(BinaryTree *tree, int new_val){
    if(new_val == tree -> val){
        tree -> count++;
        return;
    }

    else if (new_val < tree -> val){
        if(tree -> l == NULL){
            tree -> l = malloc(sizeof(BinaryTree));
            tree = tree -> l;
            tree -> val = new_val;
            tree -> l = NULL;
            tree -> r = NULL;
            tree -> count = 1;
            return;
        }
        else add_to_bintree(tree -> l, new_val);
    }

    else{
        if(tree -> r == NULL){
            tree -> r = malloc(sizeof(BinaryTree));
            tree = tree -> r;
            tree -> val = new_val;
            tree -> l = NULL;
            tree -> r = NULL;
            tree -> count = 1;
            return;
        }
        else add_to_bintree(tree -> r, new_val);
    }
}

//copies content of int array in BinTree
void fill_bintree(BinaryTree *dest, const int* src, int num_of_elems){
    if(num_of_elems != 0){
        dest -> val = *src;
        dest -> count = 1;
        for (int i = 1; i < num_of_elems; i++) {
            add_to_bintree(dest, src[i]);
        }
    }
}

//writes contents of BinTree
void print_bintree(BinaryTree *tree, FILE *output){
    if(tree == NULL) return;
    print_bintree(tree -> l, output);
    int size = tree -> count;
    for (int i = 0; i < size; ++i) {
        fwrite(&(tree -> val), sizeof(int), 1, output);
    }
    print_bintree(tree -> r, output);
}

int main() {
    FILE    *fi = fopen("input.bin", "rb"),
            *fo = fopen("output.bin", "wb");

    int length;
    fread(&length, sizeof(int), 1, fi);

    int *shuffle_arr = malloc(length * sizeof(int));
    fread(shuffle_arr, sizeof(int), length, fi);
    shuffle_array(shuffle_arr, length);

    BinaryTree *root = calloc(1, sizeof(BinaryTree));
    fill_bintree(root, shuffle_arr, length);

    print_bintree(root, fo);

    free(shuffle_arr);

    fclose(fi);
    fclose(fo);
    return 0;
}
