#include <iostream>
#include <fstream>
#include <mpi.h>
#include <chrono>
#include <vector>
#include <map>

#include "NQueen.hpp"

using namespace std;

typedef unsigned short us;
typedef unsigned long long ull;

int parallelTest(NQueen nqueen, map<us, ull> solutionMap) {
    ull subtotal;
    ull total = 0;
    ofstream myfile;

    if (nqueen.getMyRank() == 0) {
        myfile.open("testF.txt");
        myfile << "Number of parallel processes: " << nqueen.getWorldSize() << "\n";
        myfile << "Depth of initial divide: " << nqueen.getDepth() << "\n";
        myfile << "Description of test: testing new var types" << "\n";
    }

    for (us N = 13; N < 14; N++) {
        nqueen.setN(N);
        nqueen.generateArrays("calculatedValues.txt");
        MPI_Barrier(MPI_COMM_WORLD);
        vector<vector<us>> worldSizeBoard = nqueen.fileToVector("calculatedValues.txt");
        if (nqueen.getMyRank() == 0) {
            myfile << "N = " << N << "\n";
            cout << "Value: " << N << std::endl;
        }
        for (us i = 0; i < 10; i++) {
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            subtotal = nqueen.runParallel(worldSizeBoard);
            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            if (nqueen.getMyRank() == 0) {
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

    return 1;
}

int serialTest(NQueen nqueen, map<us, ull> solutionMap) {

    if (nqueen.getMyRank() == 0) {
        ull total = 0;
        ofstream myfile;
        vector<us> board;


        myfile.open("testSerialA.txt");
        myfile << "Description of test: first serial test with no initial tree calculated" << "\n";
        for (us N = 4; N < 15; N++) {
            nqueen.setN(N);
            board = nqueen.createBoard(N);
            myfile << "N = " << N << "\n";
            cout << "Value: " << N << std::endl;
            for (int i = 0; i < 10; i++) {
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                total = nqueen.nqueens(0, board);
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

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
    return 1;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    // Get the number of processes
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    //Get rank of the processes
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

    us depth = 6;
    NQueen nqueen(8, depth, worldSize, myRank);

    std::map<us, ull> solutionMap = {
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

    //serialTest(nqueen, solutionMap);

    parallelTest(nqueen, solutionMap);


    MPI_Finalize();

}