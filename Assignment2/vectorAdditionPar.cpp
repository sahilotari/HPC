#include <omp.h>
#include <pthread.h>
#include <stdio.h>

int main() {
    int N = 200;
    int A[200];
    for (int i = 0; i < N; i++)
        A[i] = 10;

    int B[200];
    for (int i = 0; i < N; i++)
        B[i] = 20;

    int C[200] = {0};
    double startTime = omp_get_wtime();
    #pragma omp parallel for reduction(+ : C)
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
        printf("Index is %d Thread is %d\n", i, omp_get_thread_num());
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", C[i]);
    }

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("\nTime taken is %f\n", time);
    return 0;
}