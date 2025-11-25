// gedit prog3_bcast.c
// mpicc prog3_bcast.c -o bcast
// mpirun -np 4 ./bcast

/* prog3_bcast.c */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        value = 42;
        printf("Process 0 broadcasting value %d\n", value);
    }

    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received value %d after broadcast\n", rank, value);

    MPI_Finalize();
    return 0;
}
