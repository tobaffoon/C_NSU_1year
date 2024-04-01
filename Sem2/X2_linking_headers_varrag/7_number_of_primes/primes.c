#include "primes.h"
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#define MAX_VALUE 10000020

//eratosthenes[i] = number of prime p's such that p <= i
static int32_t *eratosthenes;

static void sieve_eratosthenes(){
    static int def = 1;
    if(def == 1) {
        eratosthenes = calloc(MAX_VALUE, sizeof(int32_t));
        eratosthenes[0] = 0;
        eratosthenes[1] = 0;
        for (uint64_t i = 2; i < MAX_VALUE; i++) {
            if (eratosthenes[i] != -1) {
                for (uint64_t j = i * i; j < MAX_VALUE; j += i) {
                    //mark all non-prime numbers, also it allows us to keep correct number of primes <= i
                    eratosthenes[j] = -1;
                }
            }
            eratosthenes[i] += 1 + eratosthenes[i-1];
        }
        def = 0;
    }
}

int isPrime (int x){
    sieve_eratosthenes();
    if(x == 0 || eratosthenes[x] == eratosthenes[x-1])
        return 0;
    else
        return 1;
}

int findNextPrime (int x){
    sieve_eratosthenes();

    if(x == 0)
        return 2;

    while(eratosthenes[x] == eratosthenes[x-1])
        x++;

    return x;
}


int getPrimesCount(int l, int r) {
    sieve_eratosthenes();
    if(r <= 1)
        return 0;

    int res = eratosthenes[r-1] - eratosthenes[l];
    if (isPrime(l))
        res++;
    return res;
}
/*
int getPrimesCount(int l, int r){
    */
/*if(l == r)
        return 0;
    int count = 0;

    if(l - r <= 1000) {
        l = findNextPrime(l);

        while (l < r) {
            count++;
            l++;
            l = findNextPrime(l);
        }
    }*//*


    if(r < 2)
        return 0;
    if(l < 2)
        l = 2;
    if(l == r)
        return 0;

    int erat_size = sqrt(r) + 1;
    //array of flags: if eratosthenes[i] == 1, i is not prime; if eratosthenes[i] == 0, then i is prime;
    int8_t *eratosthenes = calloc(r, sizeof(int8_t));
    eratosthenes[0] = 1;
    eratosthenes[1] = 1;
    //determine first primes for segmented sieve
    for (int i = 2; i < erat_size; i++) {
        if(eratosthenes[i] == 0){
            for (int j = i * i; j < erat_size; j += i) {
                eratosthenes[j] = 1;
            }
        }
    }

    //number of primes
    int count = r - l;
    //same as "eratosthenes", but for numbers [l; r)
    int8_t *flags = calloc(count, sizeof(int8_t));

    for (int i = 2; i < erat_size; i++) {
        if(eratosthenes[i] == 1)
            continue;

        //first number f such that: f * i >= l and f * i is not prime (f != 1)
        int first_match = l / i;
        //closest f != 1 is 2
        if(first_match <= 1)
            first_match = 2;
        //if l > i and is not divisible by it, then quotient is floored thus actually smaller than we need
        //for example 75/37 = 2, 2 * 37 = 74, but 74 < 75
        else if(!DIVIDES(i, l))
            first_match ++;

        for (int j = first_match * i; j < r; j += i) {
            if(flags[j - l] == 0)
                //if j is composite, then count has one less prime
                count--;
            flags[j - l] = 1;
        }
    }

    free(flags);
    free(eratosthenes);
    return count;
}*/
