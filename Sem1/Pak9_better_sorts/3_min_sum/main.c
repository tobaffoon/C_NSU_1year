#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
int merge (long long *a, long long ak, long long *b, long long bk){
    long long *buf = malloc(sizeof(long long) * (ak + bk)), *a1 = a;
    long long totalk = ak+bk;
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
        memcpy(buf, b, bk * sizeof(long long));
        buf -= totalk - bk;
    }
    else{
        memcpy(buf, a, ak * sizeof(long long));
        buf -= totalk - ak;
    }
    a = a1;
    memcpy(a, buf, totalk*sizeof(long long));
    free(buf);
    return 1;
}
long long* merge_sort(long long *a, long long size){
    if(size > 2){
        merge(merge_sort(a, size/2), size/2, merge_sort(a + size/2, (size+1)/2), (size+1)/2);
    }
    else if(*a > *(a+1) && size != 1){
        long long temp = *a;
        *a = *(a+1);
        *(a+1) = temp;
    }
    return a;
}
void read_arr(FILE *in, long long *a, long long length){
    for(int i = 0 ; i < length; i++){
        fscanf(in, "%lld", a+i);
    }
}
/*void write_arr(FILE *out, long long *a, long long length){
    for(int i = 0 ; i < length; i++){
        fprintf(out, "%lld ", *a);
        a++;
    }
    fprintf(out, "\n");
}*/
long long count_mins_sum(long long *a, long long length){
    long long sum = 0;
    for(int i = 1 ; i < length; i++){
        sum += *a * (length - i);
        a++;
    }
    return sum;
}
int main() {
    FILE *fi, *fo;
    fi = fopen("input.txt", "rt");
    fo = fopen("output.txt", "wt");
    long long len;
    fscanf(fi, "%lld", &len);
    long long *arr = malloc(sizeof(long long) * len);
    read_arr(fi, arr, len);
    merge_sort(arr, len);
//    write_arr(fo, arr, len);
    long long minsum = count_mins_sum(arr, len);
    fprintf(fo, "%lld", minsum);
    free(arr);
    fclose(fi);
    fclose(fo);
    return 0;
}
