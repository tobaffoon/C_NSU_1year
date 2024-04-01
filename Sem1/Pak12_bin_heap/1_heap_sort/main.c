#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct BinHeap{
    int *tree;
    uint32_t cur_size;
} BinHeap;

BinHeap*    allocate_BH     (uint32_t length);
void        swap            (int *a, int *b);
void        siftup          (BinHeap *heap, uint32_t idx);
void        siftdown        (BinHeap *heap, uint32_t idx);
void        BH_add          (BinHeap *heap, int new_val);
void        heapsort        (BinHeap *heap);
void        read_BH         (BinHeap *bheap, uint32_t num_of_elems, FILE *input);
void        write_BH        (BinHeap *bheap, FILE *output);

//swaps memory contents of valuables
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//returns pointer to allocated memory for Binary Heap
BinHeap* allocate_BH(uint32_t length){
    BinHeap *ar = malloc(sizeof(BinHeap));
    ar -> tree = malloc(sizeof(int) * length);
    ar -> cur_size = 0;
    return ar;
}

//ensures that children are bigger than their parents
void siftup(BinHeap *heap, uint32_t idx){
    if(idx == 0) return;
    uint32_t dad = (idx + 1) / 2 - 1;
    if(heap -> tree[idx] > heap -> tree[dad]){
        swap(heap -> tree + idx, heap -> tree + dad);
        siftup(heap, dad);
    }
}

//ensures that parents are smaller than their children
void siftdown(BinHeap *heap, uint32_t idx){
    uint32_t    smallest = idx,
                left_child = 2*idx + 1,
                right_child = 2*idx + 2;

    //smallest is idx of the smallest of parent and its children
    if(left_child < heap -> cur_size && heap -> tree[left_child] > heap -> tree[idx]){
        smallest = left_child;
    }

    if(right_child < heap -> cur_size && heap -> tree[right_child] > heap -> tree[smallest]){
        smallest = right_child;
    }

    if(smallest != idx){
        swap(heap -> tree + idx, heap -> tree + smallest);
        siftdown(heap, smallest);
    }
}

//adds new_val to our Binary Heap
void BH_add(BinHeap *heap, int new_val){
    heap -> tree[(heap -> cur_size) ++] = new_val;
    siftup(heap, heap -> cur_size - 1);
}

void heapsort(BinHeap *heap){
    while(heap -> cur_size != 0){
        swap(heap -> tree, heap -> tree + (heap -> cur_size - 1));
        heap -> cur_size -= 1;
        siftdown(heap, 0);
    }
}

void read_BH(BinHeap *bheap, uint32_t num_of_elems, FILE *input){
    for(int i = 0; i < num_of_elems; i++){
        int new;
        fread(&new, sizeof(int), 1, input);
        add(bheap, new);
    }
}

void write_BH(BinHeap *bheap, FILE *output){
    uint32_t len = bheap -> cur_size;
    for (int i = 0; i < len; i++) {
        fwrite(bheap -> tree + i, sizeof(int), 1, output);
    }
}

int main() {
    FILE    *fi = fopen("input.bin", "rb"),
            *fo = fopen("output.bin", "wb");

    uint32_t len;
    fread(&len, sizeof(len), 1, fi);

    BinHeap *array = allocate_BH(len);
    read_BH(array, len, fi);

    heapsort(array);
    array->cur_size = len;

    write_BH(array, fo);
    fclose(fi);
    fclose(fo);
    return 0;
}
