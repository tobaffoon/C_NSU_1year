#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Factors {
    int k;
    int primes [32];
    int powers [32];
} Factors;

extern void Factorize (int X, Factors *res);
extern void find_primes();

void null_fact(Factors *fact){
    fact -> k = 0;
    for (int i = 0; i < 32; i++) {
        fact -> powers[i] = 0;
        fact -> primes[i] = 0;
    }
}

void fprint_fact(FILE *out, int X, Factors f){
    fprintf_s(out, "%d = ", X);
    if(f.k == 0) {
        fprintf_s(out, "1");
    }

    else {
        int boarder = f.k - 1;
        for (int i = 0; i < boarder; i++) {
            fprintf_s(out, "%d^%d * ", f.primes[i], f.powers[i]);
        }
        fprintf_s(out, "%d^%d", f.primes[f.k - 1], f.powers[f.k - 1]);
    }
    fprintf_s(out, "\n");
}

int main() {
    FILE    *fi = fopen("input.txt", "r"),
            *fo = fopen("output.txt", "w");

    int ns,
        curn;

    Factors curf;

    fscanf(fi, "%d", &ns);

    for (int i = 0; i < ns; i++) {
        null_fact(&curf);
        fscanf(fi, "%d", &curn);
        Factorize(curn, &curf);
        fprint_fact(fo, curn, curf);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
