/* prog2_scatter_gather.c */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int root = 0;
    int n_per_proc = 2;
    int sendbuf[8];   // assume size=4 => 8 elements
    int recvbuf[2];

    if (rank == root) {
        // Initialize array: 1 2 3 4 5 6 7 8
        for (int i = 0; i < size * n_per_proc; i++)
            sendbuf[i] = i + 1;
    }

    MPI_Scatter(sendbuf, n_per_proc, MPI_INT,
                recvbuf, n_per_proc, MPI_INT,
                root, MPI_COMM_WORLD);

    printf("Process %d received: ", rank);
    for (int i = 0; i < n_per_proc; i++) {
        printf("%d ", recvbuf[i]);
        // Example work: double the values
        recvbuf[i] *= 2;
    }
    printf("\n");

    MPI_Gather(recvbuf, n_per_proc, MPI_INT,
               sendbuf, n_per_proc, MPI_INT,
               root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("After gather at root: ");
        for (int i = 0; i < size * n_per_proc; i++)
            printf("%d ", sendbuf[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
