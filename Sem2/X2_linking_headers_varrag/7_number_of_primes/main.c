#include <assert.h>
#include "primes.h"

int main() {
    int a = findNextPrime(4423);
    assert(a == 4423);
    a = findNextPrime(10000000);
    assert(a == 10000019);
    a = findNextPrime(9999990);
    assert(a == 9999991);
    a = findNextPrime(5582);
    assert(a == 5591);
    assert(isPrime(a));
    a = 3826382;
    assert(!isPrime(a));
    a = 0;
    assert(!isPrime(a));
    a = 1;
    assert(!isPrime(a));
    a = 2;
    assert(isPrime(a));
    a = 10000000;
    assert(!isPrime(a));
    a = getPrimesCount(4861, 4871);
    assert(a == 1);
    a = getPrimesCount(4702, 4752);
    assert(a == 6);
    a = getPrimesCount(4818, 4830);
    assert(a == 0);
    a = getPrimesCount(3, 3);
    assert(a == 0);
    a = getPrimesCount(1, 782853);
    assert(a == 62679);
    a = getPrimesCount(4876540, 10000000);
    assert(a == 324161);
    a = getPrimesCount(1, 10000000);
    assert(a == 664579);
}
