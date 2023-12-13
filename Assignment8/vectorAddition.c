%% cu
#include <stdio.h>
__global__ void addVector(int *v1, int *v2, int *result, int N)
{
    int i = threadIdx.x;
    if (i < N)
    {
        result[i] = v1[i] + v2[i];
    }
}
int main()
{
    int N = 100;
    int v1[N], v2[N], result[N];
    for (int i = 0; i < N; i++)
    {
        v1[i] = 1;
        v2[i] = 2;
    }
    //  initializing poiters for device vectors
    int *d_v1, *d_v2, *d_result;

    // allocating memory for the device vectors
    cudaMalloc(&d_v1, N * sizeof(int));
    cudaMalloc(&d_v2, N * sizeof(int));
    cudaMalloc(&d_result, N * sizeof(int));

    // copying from host to device
    cudaMemcpy(d_v1, v1, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_v2, v2, N * sizeof(int), cudaMemcpyHostToDevice);

    addVector<<<1, N>>>(d_v1, d_v2, d_result, N);
    cudaDeviceSynchronize();

    // copying from device to host
    cudaMemcpy(result, d_result, N * sizeof(int), cudaMemcpyDeviceToHost);
    for (int i = 0; i < N; i++)
    {
        printf("%d ", result[i]);
    }
    return 0;
}
