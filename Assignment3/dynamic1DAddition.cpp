#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10000000
int main()
{
    double startTime, endTime, time;
    startTime = omp_get_wtime();
    int *a = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);
    int b = 10;
    omp_set_num_threads(100);
    for (int i = 0; i < N; i++)
    {
        a[i] = 0;
    }

#pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++)
    {
        c[i] = a[i] + b;
    }
    endTime = omp_get_wtime();
    time = endTime - startTime;
    printf("\nTime taken is %f\n", time);
}