// #include <stdio.h>
// #include <omp.h>
// #include <time.h>

// #define n 250
// #define num_threads 4

// void parallelPrefixSum(int arr[])
// {
//     int prefixSum[n];
//     prefixSum[0] = arr[0];

// #pragma omp parallel for schedule(dynamic)
//     for (int i = 1; i < n; i++)
//     {
//         prefixSum[i] = prefixSum[i - 1] + arr[i];
//     }

//     printf("Parallel Prefix Sum Array:\n");
//     for (int i = 0; i < n; i++)
//     {
//         printf("%d ", prefixSum[i]);
//     }
//     printf("\n");
// }

// int main()
// {
//     clock_t start = clock();
//     printf("The number of elements in the array: ");

//     printf("The elements of the array:\n");
//     int arr[n];
//     for (int i = 0; i < n; i++)
//     {
//         arr[i] = i;
//         printf("%d ", arr[i]);
//     }
//     printf("\n");

//     parallelPrefixSum(arr);

//     clock_t end = clock();

//     double t = (double)(end - start) / CLOCKS_PER_SEC;

//     printf("Size of Vector: %d\n", n);
//     printf("Number of threads: %d\n", num_threads);
//     printf("Time taken = %f seconds.\n", t);
//     printf("Speedup = %f\n", 0.047 / t);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
// void parallelPrefixSum(int *arr, int *ans, int n) {
//     ans[0] = arr[0];  // Initialize the first element of the output array

//     #pragma omp parallel
//     {
//         int num_threads = omp_get_num_threads();
//         int thread_id = omp_get_thread_num();
//         int chunk_size = n / num_threads;
//         int start = thread_id * chunk_size;
//         int end = (thread_id == num_threads - 1) ? n : start + chunk_size;

//         for (int i = start + 1; i < end; i++) {
//             ans[i] = ans[i - 1] + arr[i];
//         }
//     }
// }

void parallelPrefixSum(int *arr, int *ans, int n) {
    ans[0] = arr[0];  // Initialize the first element of the output array

    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int chunk_size = n / num_threads;
        int start = thread_id * chunk_size;
        int end = (thread_id == num_threads - 1) ? n : start + chunk_size;

        for (int i = start + 1; i < end; i++) {
            ans[i] = arr[i] + ans[i - 1];
        }
        

        #pragma omp barrier

        // Calculate the offset for each thread
        int offset = 0;
        if (thread_id > 0) {
            offset = ans[start - 1];
        }

        // Update the output array with the prefix sum
        for (int i = start; i < end; i++) {
            ans[i] += offset;
        }
    }
}
int main()
{
    clock_t start, end;
    int n = 12;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr;
    arr = (int *)malloc(n * sizeof(int));
    int * ans;
    ans = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = i+1;
        ans[i] = i+1;
    }
    start = clock();
    parallelPrefixSum(arr, ans, n);

    end = clock();
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Prefix Sum: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
    printf("\n Time taken for execution in seconds: %f \n", duration);
    return 0;
}

// #include <iostream>
// #include <vector>
// #include <omp.h>
// using namespace std;

// void parallelPrefixSum(std::vector<int>& input) {
//     int numThreads = omp_get_max_threads();
//     int n = input.size();
    
//     #pragma omp parallel
//     {
//         int tid = omp_get_thread_num();
//         int chunkSize = n / numThreads;
//         int startIndex = tid * chunkSize;
//         int endIndex = (tid == numThreads - 1) ? n : startIndex + chunkSize;

//         // Perform local prefix sum within each thread
//         for (int i = startIndex + 1; i < endIndex; i++) {
//             input[i] += input[i - 1];
//         }

//         // Synchronize to ensure all threads finish local prefix sum
//         #pragma omp barrier

//         // Adjust the rest of the array based on the local prefix sum
//         if (tid > 0) {
//             int prefixSum = input[startIndex - 1];
//             for (int i = startIndex; i < endIndex; i++) {
//                 input[i] += prefixSum;
//             }
//         }
//     }
// }

// int main() {
//     std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8};

//     parallelPrefixSum(input);

//     // Print the result
//     for (int i : input) {
//         std::cout << i << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
