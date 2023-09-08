#include <stdio.h>
#include <omp.h>
#include<sys/time.h>

#define N 8  // Size of matrices

void matrixMatrixMultiplication(int A[][N], int B[][N], int result[][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void initial(int A[][N]){
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
                A[i][j] = i+j;
        }
    }
}

int main() {
    clock_t start, end;
    start = clock();
    int matrixA[N][N] = {0};
initial(matrixA);
    int matrixB[N][N] = {0};
initial(matrixB);
    int result[N][N] = {0};

    matrixMatrixMultiplication(matrixA, matrixB, result);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    end = clock();
    double duration = ((double)end-start)/CLOCKS_PER_SEC;
    printf("Time Taken: %f",duration);

    return 0;
}