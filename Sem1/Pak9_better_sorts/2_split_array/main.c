#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

int partition(int *a, int n, int pivot){
    int *less = calloc(n, sizeof(int));
    int *bigger = calloc(n, sizeof(int));
    char eq_state = 0;
    int less_length = 0;
    for (int i = 0; i < n; i++) {
        if(*a == pivot){
            if(eq_state == 0){
                *less = *a;
                less++;
                less_length++;
                eq_state = 1;
            }
            else{
                *bigger = *a;
                bigger++;
                eq_state = 0;
            }
        }
        else if(*a < pivot){
            *less = *a;
            less++;
            less_length++;
        }
        else{
            *bigger = *a;
            bigger++;
        }
        a++;
    }
    less -= less_length;
    bigger -= (n - less_length);
    a -= n;
    memcpy(a, less, sizeof(int) * less_length);
    memcpy(a+less_length, bigger, sizeof(int) * (n - less_length));
    free(less);
    free(bigger);
    return less_length;
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wb");
    int length, comp_number;
    fread(&length, sizeof(length), 1, fi);
    fread(&comp_number, sizeof(comp_number), 1, fi);
    int *arr = malloc(sizeof(int) * length);
    fread(arr, sizeof(int), length, fi);
    int smaller_len = partition(arr, length, comp_number);
    fwrite(&smaller_len, sizeof(int), 1, fo);
    fwrite(arr, sizeof(int), length, fo);
    fclose(fi);
    fclose(fo);
    return 0;
}
