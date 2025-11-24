/* prog1_send_recv.c */
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int msg;
    if (rank == 0) {
        for (int dest = 1; dest < size; dest++) {
            msg = dest * 10;
            MPI_Send(&msg, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            printf("Process 0 sent %d to process %d\n", msg, dest);
        }
    } else {
        MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received %d from process 0\n", rank, msg);
    }

    MPI_Finalize();
    return 0;
}
