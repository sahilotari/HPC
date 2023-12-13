#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 4

void sumLowerTriangularMatrices(int A[][N], int B[][N], int C[][N]) {
    int i, j;
    #pragma omp parallel for private(i,j)
    for (i = 0; i < N; i++) {
        for (j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    omp_set_num_threads(8);
    int A[N][N], B[N][N], C[N][N];
    double startTime = omp_get_wtime();
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            A[i][j] = i+j;
            B[i][j] = i+2*j;
        }
    }

    // Sum the matrices using OpenMP
    sumLowerTriangularMatrices(A, B, C);
    double endTime = omp_get_wtime();

    printf("Time taken (Par): %f\n", endTime - startTime);
    // Display the result matrix C (sum of A and B)
    // printf("Matrix C :\n");
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j <= i; j++) {
    //         printf("%d ", C[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}