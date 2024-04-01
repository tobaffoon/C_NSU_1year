#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
int merge (int *a, int ak, int *b, int bk){
    int *buf = malloc(sizeof(int) * (ak + bk)), *a1 = a;
    int totalk = ak+bk;
    while(ak && bk){
        if(*a < *b){
            *buf = *a;
            ak--;
            if(ak) a++;
        }
        else{
            *buf = *b;
            bk--;
            if(bk) b++;
        }
        buf++;
    }
    if(ak == 0) {
        memcpy(buf, b, bk * sizeof(int));
        buf -= totalk - bk;
    }
    else{
        memcpy(buf, a, ak * sizeof(int));
        buf -= totalk - ak;
    }
    a = a1;
    memcpy(a, buf, totalk*sizeof(int));
    free(buf);
    return 1;
}
int* merge_sort(int *a, int size){
    if(size > 2){
        merge(merge_sort(a, size/2), size/2, merge_sort(a + size/2, (size+1)/2), (size+1)/2);
    }
    else if(*a > *(a+1) && size != 1){
        int temp = *a;
        *a = *(a+1);
        *(a+1) = temp;
    }
    return a;
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rb");
    fo = fopen("output.txt", "wb");
    int len;
    fread(&len, sizeof(int), 1,fi);
    int *arr = malloc(sizeof(int) * len);
    fread(arr, sizeof(int), len, fi);
    merge_sort(arr, len);
    fwrite(arr, sizeof(int), len, fo);
    free(arr);
    fclose(fi);
    fclose(fo);
    return 0;
}
