#include <omp.h>
#include <stdio.h>
#include <time.h>
#define n 100000
void sort(int nums[]){
    int i, j;
    for (i = 0; i < n; i++)
    {
        int turn = i % 2;
#pragma omp parallel for
        for (j = turn; j < n - 1; j += 2){
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}
void sort_des(int nums[]){
    int i, j;
    for (i = 0; i < n; ++i){
        int turn = i % 2;
#pragma omp parallel for
        for (j = turn; j < n - 1; j += 2){
            if (nums[j] < nums[j + 1]){
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int vec1[n], vec2[n];
    for (int i = 0; i < n; i++)
    {
        vec1[i] = 15;
    }
    for (int i = 0; i < n; i++)
    {
        vec2[i] = 300;
    }
    clock_t t;
    t = clock();
    sort(vec1);
    sort_des(vec2);
    t = clock() - t;

    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken (par): %f\n", time_taken);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + (vec1[i] * vec2[i]);
    }
    printf("%d\n", sum);
    return 0;
}