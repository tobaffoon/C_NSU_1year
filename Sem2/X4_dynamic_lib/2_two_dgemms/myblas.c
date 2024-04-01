void cblas_dgemm(const int Order, const int TransA, const int TransB, const int M, const int N, const int K,
                 const double alpha, const double *A, const int lda, const double *B, const int ldb, const double beta, double *C,
                 const int ldc) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] *= beta;
            for (int l = 0; l < K; l++) {
                C[i * N + j] += alpha * A[i * K + l] * B[l * N + j];
            }
        }
    }
}
