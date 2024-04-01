#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define DIVIDES(D, N) ((N) % (D) == 0)
#define ISPRIME 1
#define ISNPRIME 0

typedef struct Factors {
    int k;
    int primes [32];
    int powers [32];
} Factors;

/*int8_t is_prime(int X){
    int sqr_x = sqrt(X);
    for (int i = 2; i <= sqr_x; i++) {
        if(DIVIDES(i, X))
            return ISNPRIME;
    }
    return ISPRIME;
}*/

void Factorize (int X, Factors *res){
    int curk,
        sqr_x = sqrt(X);

    for (int i = 2; i <= sqr_x; ++i) {
        if(DIVIDES(i, X)){
            curk = res -> k;
            res -> primes[curk] = i;
            res -> powers[curk] = 1;
            res -> k ++;
            X /= i;
        }
        while (DIVIDES(i, X)) {
            res -> powers[curk] ++;
            X /= i;
        }
    }


    if(X != 1){
        res -> primes[res -> k] = X;
        res -> powers[res -> k] = 1;
        res -> k ++;
    }
}