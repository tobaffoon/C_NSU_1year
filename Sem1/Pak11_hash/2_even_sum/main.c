#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node *next;
} Node;

typedef void (*callback)(void *ctx, int* value);

void read_arr       (int* array, Node *list, int length, FILE *input);
void arrayForeach   (void *ctx, callback func, int *arr, int n);
void listForeach    (void *ctx, callback func, Node *list, int n);

void read_arr(int* array, Node *list, int length, FILE *input){
    for (int i = 0; i < length; i++) {
        fscanf(input, "%d", array + i);
        list -> value = array[i];
        list -> next = malloc(sizeof(Node));
        list = list -> next;
    }
}

void add(void *a, int *b){
    if(*b % 2 == 0) *(int*)a += *b;
}

void arrayForeach(void *ctx, callback func, int *arr, int n){
    for (int i = 0; i < n; i++) {
        func((int*)ctx, arr + i);
    }
}

void listForeach(void *ctx, callback func, Node *list, int n){
    for (int i = 0; i < n; i++) {
        func((int*)ctx, &(list -> value));
        list = list -> next;
    }
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    callback even_sum = add;
    int n;
    fscanf(fi, "%d", &n);

    int *arr = malloc(sizeof(int) * n);
    Node *head = malloc(sizeof(Node));
    read_arr(arr, head, n, fi);

    int sum = 0;
    arrayForeach((void*)&sum, even_sum, arr, n);
    fprintf(fo, "%d ", sum);

    sum = 0;
    listForeach((void*)&sum, even_sum, head, n);
    fprintf(fo, "%d ", sum);

    fclose(fi);
    fclose(fo);
    return 0;
}
