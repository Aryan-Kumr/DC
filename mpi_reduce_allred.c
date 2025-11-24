/* prog4_reduce_allreduce.c */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int local_val;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_val = rank + 1;  // 1,2,3,... for ranks 0,1,2,...

    int sum, max, min, prod;
    int all_sum;

    MPI_Reduce(&local_val, &sum,  1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &max,  1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &min,  1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_val, &prod, 1, MPI_INT, MPI_PROD,0, MPI_COMM_WORLD);

    MPI_Allreduce(&local_val, &all_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Using MPI_Reduce at root:\n");
        printf("  SUM  = %d\n", sum);
        printf("  MAX  = %d\n", max);
        printf("  MIN  = %d\n", min);
        printf("  PROD = %d\n", prod);
    }

    printf("Process %d sees ALLREDUCE SUM = %d\n", rank, all_sum);

    MPI_Finalize();
    return 0;
}
