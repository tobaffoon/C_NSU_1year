#include "myblas.h"

void dgemv(
        int m, int n,
        double alpha, const double *A, const double *X,
        double beta, double *Y
){
    for (int i = 0; i < m; i++) {
        Y[i] *= beta;
        for (int j = 0; j < n; j++) {
            Y[i] += alpha * A [i * n + j] * X[j];
        }
    }
}

void dger(
        int m, int n,
        double alpha, const double *X, const double *Y,
        double *A
){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A [i * n + j] += alpha * Y[j] * X[i];
        }
    }
}