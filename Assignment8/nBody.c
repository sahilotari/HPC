%%cu
#include <stdio.h>
#include <math.h>

const float G = 6.67430e-11; // Gravitational constant
const float SOFTENING = 1e-9; // Softening factor to avoid singularities

_global_ void computeForces(float* pos, float* forces, int n, float* mass) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < n) {
        float curX = pos[2*idx];
        float curY = pos[2*idx+1];
        forces[2*idx] = 0.0f;
        forces[2*idx+1] = 0.0f;

        for (int j = 0; j < n; j++) {
            if (j != idx) {
                float deltaX = pos[2*j] - curX;
                float deltaY = pos[2*j+1] - curY;
                float dist = sqrt(deltaX*deltaX + deltaY*deltaY);
                float force = G * mass[idx] * mass[j] / (dist * dist + SOFTENING*SOFTENING);
                forces[2*idx] += force * deltaX / dist;
                forces[2*idx+1] += force * deltaY / dist;
            }
        }
    }
}

int main() {
    const int n = 1000;
    const int numIterations = 1000;

    float* h_pos;
    float* h_forces;
    float* d_pos;
    float* d_forces;
    float* d_mass;

    size_t size = 2 * n * sizeof(float);

    h_pos = (float*)malloc(size);
    h_forces = (float*)malloc(size);

    
    for (int i = 0; i < 2 * n; i++) {
        h_pos[i] = rand() / (float)RAND_MAX;
    }

    float* h_mass = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        h_mass[i] = 1.0f;
    }

    cudaMalloc(&d_pos, size);
    cudaMalloc(&d_forces, size);
    cudaMalloc(&d_mass, n * sizeof(float));

    cudaMemcpy(d_pos, h_pos, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_mass, h_mass, n * sizeof(float), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    for (int iter = 0; iter < numIterations; iter++) {
        computeForces<<<blocksPerGrid, threadsPerBlock>>>(d_pos, d_forces, n, d_mass);

        // Update positions based on forces and velocities
        // You should implement this based on your specific scenario.

        // Reset forces for the next iteration
        cudaMemset(d_forces, 0, size);
    }

    cudaMemcpy(h_pos, d_pos, size, cudaMemcpyDeviceToHost);

    // Print out the positions after the simulation
    for (int i = 0; i < n; i++) {
        printf("Particle %d: x = %f, y = %f\n", i, h_pos[2*i], h_pos[2*i+1]);
    }

    // Clean up
    free(h_pos);
    free(h_forces);
    free(h_mass);
    cudaFree(d_pos);
    cudaFree(d_forces);
    cudaFree(d_mass);

    return 0;
}