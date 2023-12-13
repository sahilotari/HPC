#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000
int main(){
    omp_set_num_threads(180);
    double startTime, endTime, time;
    startTime = omp_get_wtime();
    int *a = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    int b = 10;
    
    for (int i = 0; i < N; i++)
    {
        a[i] = 0;
    }
    
#pragma omp parallel for schedule(static, 2)
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b;
    }
    endTime = omp_get_wtime();
    time = endTime - startTime;
    printf("\nTime taken is %f\n", time);
}