#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 100000000; // 1e8
    long long sum = 0;
    long long i;

    double start = omp_get_wtime();

    #pragma omp parallel for private(i) reduction(+:sum)
    for (i = 1; i <= N; i++) {
        sum += i;
    }

    double end = omp_get_wtime();

    printf("Sum of first %lld integers = %lld\n", N, sum);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
