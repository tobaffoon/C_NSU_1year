#include <stdio.h>
int b[10000]={0};
int main() {
    FILE *fpw, *fpr;
    fpw = fopen("output.txt", "w");
    fpr = fopen("input.txt", "r");
    int n;
    fscanf(fpr, "%d", &n);
    int a;
    for(int i=0; i<n; i++){
        fscanf(fpr, "%d", &a);
        b[a-1]++;
    }
    for(int i=0; i<10000; i++){
        if(b[i]) fprintf(fpw, "%d: %d\n", i+1, b[i]);
    }
    return 0;
}
