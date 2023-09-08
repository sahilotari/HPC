#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000

int main() {
    int i, num_inside = 0;
    double x, y;

    // Set the seed for random number generation
    srand(52525);
    double startTime = omp_get_wtime();
    #pragma omp parallel for private(x, y) reduction(+:num_inside)
    for (i = 0; i < N; i++) {
        // Generate random points within the unit square
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point is inside the quarter-circle (radius <= 1)
        if (x * x + y * y <= 1.0) {
            num_inside++;
        }
    }

    // Estimate Pi using the Monte Carlo method
    double pi = 4.0 * num_inside / N;

    printf("Estimated Pi Value: %f\n", pi);

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("\nTime taken is %f\n", time);
    return 0;
}