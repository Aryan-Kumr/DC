/* prog7_omp_pi.c */
#include <stdio.h>
#include <omp.h>

int main() {
    long long num_steps = 10000000; // 10 million
    double step = 1.0 / (double)num_steps;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    printf("Estimated value of pi = %.10f\n", pi);
    return 0;
}
