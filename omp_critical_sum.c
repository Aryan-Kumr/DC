#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4;
    int global_sum = 0;

    #pragma omp parallel num_threads(num_threads) shared(global_sum)
    {
        int tid = omp_get_thread_num();

        #pragma omp critical
        {
            global_sum += tid;
            printf("Thread %d updated global_sum to %d\n", tid, global_sum);
        }
    }

    printf("Final global_sum = %d\n", global_sum);
    return 0;
}
