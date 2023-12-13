#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main() {
    int i, num_inside = 0;
    double x, y;
    omp_set_num_threads(100);
    // Set the seed for random number generation
    srand(52525);
    double startTime = omp_get_wtime();
    #pragma omp parallel private(x, y)
    {
        int local_inside = 0;

        #pragma omp for
        for (i = 0; i < N; i++) {
            // Generate random points within the unit square
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;

            // Check if the point is inside the quarter-circle (radius <= 1)
            if (x * x + y * y <= 1.0) {
                local_inside++;
            }
        }

        // Accumulate local_inside_circle values from all threads
        #pragma omp atomic
        num_inside += local_inside;
    }

    // Estimate Pi using the Monte Carlo method
    double pi = 4.0 * num_inside / N;

    printf("Estimated Pi: %f\n", pi);
    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("\nTime taken is %f\n", time);
    return 0;
}