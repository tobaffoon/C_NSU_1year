#include <stdio.h>
#include <stdlib.h>

typedef struct TSimpleArray{
    int *arr;
    int size;
} simpleArray;

simpleArray* sorted_array_diff(simpleArray *a, simpleArray *b){
    simpleArray *res = calloc(1, sizeof(simpleArray));
    res -> arr = calloc(a -> size + 1, sizeof(int));
    res -> size = 0;
    while(a -> size != 0 && b -> size != 0){
        while(a -> size > 1 && (a->arr)[1] == (a->arr)[0]){
                (a->size)--;
                (a->arr)++;
        }
        if(*(a -> arr) < *(b -> arr)){
            *(res -> arr) = *(a -> arr);
            (a -> size)--;
            (res -> size)++;
            (res -> arr)++;
            if(a -> size == 0) break;
            (a -> arr)++;
        }
        else if(*(a -> arr) == *(b -> arr)){
            (a -> size)--;
            if(a -> size == 0) break;
            (a -> arr)++;
        }
        else{
            (b -> size)--;
            if(b -> size == 0) break;
            (b -> arr)++;
        }
    }
    while(a -> size != 0) {
        while (a->size > 1 && (a->arr)[1] == (a->arr)[0]) {
            (a->size)--;
            (a->arr)++;
        }
        *(res -> arr) = *(a -> arr);
        (a -> size)--;
        (res -> size)++;
        (res -> arr)++;
        if(a -> size == 0) break;
        (a -> arr)++;
    }
    res -> arr -= res -> size;
    return res;
}

int comp(const int *a, const int *b){
    if (*a < *b){
        return -1;
    }
    if(*a == *b){
        return 0;
    }
    return 1;
}

int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");
    simpleArray arr_a, arr_b;
    fscanf(fi, "%d", &arr_a.size);
    arr_a.arr = calloc(arr_a.size, sizeof(int));
    for (int i = 0; i < arr_a.size; i++) {
        fscanf(fi, "%d", arr_a.arr + i);
    }
    fscanf(fi, "%d", &arr_b.size);
    arr_b.arr = calloc(arr_b.size, sizeof(int));
    for (int i = 0; i < arr_b.size; i++) {
        fscanf(fi, "%d", arr_b.arr + i);
    }
    qsort(arr_a.arr, arr_a.size, sizeof(int), (int (*)(const void *, const void *))comp);
    qsort(arr_b.arr, arr_b.size, sizeof(int), (int (*)(const void *, const void *))comp);
    simpleArray *arr_c = sorted_array_diff(&arr_a, &arr_b);
    fprintf(fo, "%d\n", arr_c -> size);
    for (int i = 0; i < arr_c -> size; i++) {
        fprintf(fo, "%d ", (arr_c -> arr) [i]);
    }
    fclose(fi);
    fclose(fo);
    return 0;
}
