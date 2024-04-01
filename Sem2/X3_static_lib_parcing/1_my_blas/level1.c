#include "myblas.h"
#include <string.h>
#include <stdlib.h>

void dcopy(int n, const double *X, double *Y){
    memcpy(Y, X, n * sizeof(double));
}

void dswap(int n, double *X, double *Y){
    double *temp = malloc(n * sizeof(double));
    dcopy(n, X, temp);                                                  //X -> temp
    dcopy(n, Y, X);                                                     //Y -> X
    dcopy(n, temp, Y);                                                  //temp(X) -> Y
    free(temp);
}

void dscal(int n, double alpha, double *X){
    for (int i = 0; i < n; i++) {
        X[i] *= alpha;
    }
}

void daxpy(int n, double alpha, const double *X, double *Y){
    for (int i = 0; i < n; i++) {
        Y[i] += X[i] * alpha;
    }
}

double ddot(int n, const double *X, const double *Y){
    double res = 0;
    for (int i = 0; i < n; i++) {
        res += X[i] * Y[i];
    }
    return res;
}