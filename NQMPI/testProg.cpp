#include <mpi.h>
#include <iostream>
int main(int argc, char** argv) {
    // Initialize the MPI environment
    // Must run before all other MPI commands
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //Get rank of the processdes
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Print the message
    std::cout << "World Size: " << world_size << "  Rank: " << my_rank << std::endl;

    // Finalize the MPI environment.
    MPI_Finalize();
}


//mpiexec -n <number of processes> ./NQMPI.exe