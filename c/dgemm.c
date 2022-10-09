#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void MatricesMultiplication(const int M, const int N, const int K, const double* A, const double* B, double* C) {

   double start = clock();

   for (int i = 0; i < N; i++)      //col
    for (int j = 0; j < M; j++)     //row
      for (int k = 0; k < K; k++)   //mult
            C[i*M+j] += A[k*M + j] * B[i*K + k];

   double end = clock();
   printf("Work took %0.2f seconds\n", (end - start) / 1000000.0);
}

void FillMatrixWithRandomValues(const int C, const int R, double *M) {
   for (int i = 0; i < C; i++)     // col
      for (int j = 0; j < R; j++)  // row
         M[i * R + j] = rand() % 100;
}

void OutputMatrix(const int C, const int R, const double *M) {
   for (int i = 0; i < C; i++) {
      for (int j = 0; j < R; j++)
         printf("%.2f ", M[i*R+j]);
      printf("\n");
   }
   printf("\n");
}

int main() {
   int i, j;
   const int M = 2000, K = 2000, N = 2000;                  //matrices size
   double *A, *B, *C;                              //matrices ptr

   A = (double*)malloc(M * K * sizeof(double));    //init matrix A[M*K]   
   B = (double*)malloc(K * N * sizeof(double));    //init matrix B[K*N]  
   C = (double*)calloc(M * N, sizeof(double));     //init with 0 value matrix C[M*N]  

   FillMatrixWithRandomValues(K, M, A);
   FillMatrixWithRandomValues(N, K, B);

   MatricesMultiplication(M, N, K, A, B, C);
}