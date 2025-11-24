#include <stdio.h>
#include <omp.h>

long long fib(int n) {
    if (n < 2) return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 30; // keep small, tasks blow up quickly
    long long result;
    double start, end;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    end = omp_get_wtime();

    printf("fib(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
