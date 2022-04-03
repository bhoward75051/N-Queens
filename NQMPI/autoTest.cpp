#include <iostream>
#include <fstream>
#include <mpi.h>
#include <chrono>
#include <vector>
#include <map>

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

    int depth = 4;
    NQueen nqueen(3, depth, worldSize, myRank);

    int subtotal;
    unsigned long total = 0;

    std::map<int, int> solutionMap = {
        {1, 1},
        {2, 0},
        {3, 0},
        {4, 2},
        {5, 10},
        {6, 4},
        {7, 40},
        {8, 92},
        {9, 352},
        {10, 724},
        {11, 2680},
        {12, 14200},
        {13, 73712},
        {14, 365596},
        {15, 2279184},
        {16, 14772512}
    };
    ofstream myfile;
    if (myRank == 0) {
        myfile.open("testD.txt");
        myfile << "Number of parallel processes: " << worldSize << "\n";
        myfile << "Depth of initial divide: " << depth << "\n";
    }
    for (int N = 4; N < 14; N++) {
        nqueen.setN(N);
        nqueen.generateArrays("calculatedValues.txt");
        MPI_Barrier(MPI_COMM_WORLD);
        vector<vector<int>> worldSizeBoard = nqueen.fileToVector("calculatedValues.txt");
        if (myRank == 0) {
            myfile << "N = " << N << "\n";
            cout << "Value: " << N << std::endl;
        }
        for (int i = 0; i < 10; i++) {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            subtotal = nqueen.runParallel(worldSizeBoard);
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            if (myRank == 0) {
                if (total == solutionMap[N]) {
                    myfile << "Time to execute (sec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << "\n";
                    std::cout << "Time to execute (sec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << std::endl;
                }
                else {
                    myfile << "Wrong solution calculated" << "\n";
                    cout << "Wrong solution calculated. Intended value: " << solutionMap[N] << ". Actual: " << total << std::endl;

                }
            }
        }
    }
    myfile.close();

    MPI_Finalize();

}