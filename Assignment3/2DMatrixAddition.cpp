#include<stdio.h>
#include<omp.h>
#include<time.h>

#define n 200
#define num_threads 4

int main() {
    clock_t start=clock();
    printf("The size of matrix: %d\n",n);

    int mat[n][n];
    int vec[n];
    int res[n];

    printf("The elements of the matrix:\n");
    int c = 1;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            mat[i][j]=c++;
        }
    }

    printf("The elements of the vector:\n");
    for (int i = 0; i<n; i++) {
        vec[i]=1;
    }

    #pragma omp parallel for
    for (int i = 0; i<n; i++) {
        res[i] = 0;
        for (int j = 0; j<n; j++) {
            res[i] += mat[i][j] * vec[j];
        }
    }

    printf("Result vector:\n");
    for (int i = 0; i<n; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    clock_t end = clock();

    double t=(double)(end-start)/CLOCKS_PER_SEC;

    printf("Size of Vector: %d\n",n);
    printf("Number of threads: %d\n",num_threads);
    printf("Time taken = %f seconds.\n", t);
    printf("Speedup = %f\n", 0.021/t);

    return 0;
}
