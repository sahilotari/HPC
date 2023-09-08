#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5  

void sumLowerTriangularMatrices(int A[][N], int B[][N], int C[][N]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            A[i][j] = i+j;
            B[i][j] = i+2*j;
        }
    }

    // Sum the matrices using OpenMP
    sumLowerTriangularMatrices(A, B, C);

    // Display the result matrix C (sum of A and B)
    printf("Matrix C :\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}