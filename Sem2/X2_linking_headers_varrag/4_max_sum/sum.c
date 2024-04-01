#include <stdint.h>
#include <stdlib.h>
extern int *as;
extern int64_t *subsum;

void Init(const int *arr, int len){
    subsum = malloc(len * sizeof(int64_t));
    subsum[0] = arr[0];
    for (int i = 1; i < len; i++) {
        subsum[i] = arr[i] + subsum[i-1];
    }
}

int64_t Sum(int l, int r){
    if(l == r)
        return 0;
    else if(l == 0)
        return subsum[r-1];
    else
        return subsum[r-1] - subsum[l-1];
}