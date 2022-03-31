#include <iostream>
#include <fstream>
#include <mpi.h>

#include "NQueen.hpp"

using namespace std;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    // Get the number of processes
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    //Get rank of the processes
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    int N = 8;
    int depth = 3;

    NQueen nqueen(N, depth, worldSize, myRank);
    
    nqueen.generateArrays("nqtest.txt");

    int subtotal;
    subtotal = nqueen.runParallel("nqtest.txt");
    unsigned long total = 0;

    MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myRank == 0) cout << total;

    MPI_Finalize();

}