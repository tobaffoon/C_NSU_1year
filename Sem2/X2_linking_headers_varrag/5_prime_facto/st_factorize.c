#include <stdlib.h>

#define DIVIDES(D, N) ((N) % (D) == 0)
#define PRIMES (primes.nums)
#define PR_LEN (primes.pr_len)

typedef struct Factors {
    int k;
    int primes [32];
    int powers [32];
} Factors;

typedef struct Primes{
    int nums[100000];
    int pr_len;
} Primes;

Primes primes;

void find_primes(){
    int *natural = malloc(31622 * sizeof(int));             //31622 = [sqrt(10^9)]
    for (int i = 0; i < 31622; i++) {
        natural[i] = i + 1;
    }

    for (int i = 1; i < 15811; ++i) {                            //15811 = 31622 / 2
        if(natural[i] != 0) {
            int boarder = 15811 / i;
            for (int j = i + natural[i]; j < boarder; j+=natural[i]) {
                natural[j] = 0;
            }
        }
    }

    primes.pr_len = 0;

    for (int i = 1; i < 31622; i++) {
        if(natural[i] != 0){
            primes.nums[primes.pr_len] = natural[i];
            primes.pr_len++;
        }
    }
    free(natural);
}

void Factorize (int X, Factors *res){
    for (int i = 0; i < PR_LEN && PRIMES[i] <= X; i++) {
        if(DIVIDES(PRIMES[i], X)){
            int pr_idx = res->k;

            res->primes[ pr_idx ] = PRIMES[i];
            res->powers[ pr_idx ] = 1;
            res->k++;
            X /= PRIMES[i];

            while(DIVIDES(PRIMES[i], X)){
                res->powers[ pr_idx ]++;
                X /= PRIMES[i];
            }
        }
    }
}