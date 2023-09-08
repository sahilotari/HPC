#include <stdio.h>
#include <time.h>
#define n 100000

void sort(int nums[]){
    int i, j;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

void sortDesc(int nums[]){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = i + 1; j < n; j++) {
            if (nums[i] < nums[j]){
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
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
    clock_t t = clock();
    sort(vec1);
    sortDesc(vec2);
    t = clock() - t;
    double time = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken (seq): %f\n", time);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + (vec1[i] * vec2[i]);
    }
    printf("%d\n", sum);
    return 0;
}