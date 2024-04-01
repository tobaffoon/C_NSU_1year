#include "cblas.h"
void MatrixSqr(int n, const double *A, double *R){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            R[i*n + j] = 0;
        }
    }
    cblas_dgemm(101,
                111,
                111,
                n,
                n,
                n,
                1,
                A,
                n,
                A,
                n,
                0,
                R,
                n);
}