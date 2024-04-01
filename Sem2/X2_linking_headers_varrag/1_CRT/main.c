#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//return x from a*x+b*y = gcd(a,b)
uint64_t inv(uint64_t a, uint64_t b){
    static int64_t x=0, x1=0, y1=0;

    if(b == 0){
        x1 = 1;
        y1 = 0;
        return x;
    }
    else{
        inv(b, a % b);
    }
    x = y1;

    y1 = x1 - (a/b) * y1;
    x1 = x;

    return (x + b) % b;
}

uint64_t safe_sub(uint64_t f, uint64_t s, int module){
    return ((int64_t)(f-s) % module + module) % module;
}

uint64_t CRT(int len, const int *mod, const int *rem){
    uint64_t    prod = 1,
                x = 0,
                sub_prod;

    for (int i = 0; i < len; i++) {
        prod *= mod[i];
    }

    for (int i = 0; i < len; i++) {
        sub_prod = prod / mod[i];
        x += sub_prod * ((inv(sub_prod % mod[i], mod[i]) * rem[i]) % mod[i]);
    }

    return x % prod;
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int     ms,
            *mods,
            *rems;

    fscanf(fi, "%d", &ms);

    mods = malloc(ms * sizeof(int));
    rems = malloc(ms * sizeof(int));

    for (int i = 0; i < ms; i++) {
        fscanf(fi, "%d", mods + i);
    }

    for (int i = 0; i < ms; i++) {
        fscanf(fi, "%d", rems + i);
    }

    fprintf_s(fo, "%llu", CRT(ms, mods, rems));

    fclose(fi);
    fclose(fo);
    return 0;
}
