#include <iostream>
#include <fstream>
#include <mpi.h>
#include <vector>
#include <map>
#include <string>

#include "NQueen.hpp"

using namespace std;

typedef unsigned short us;
typedef unsigned long long ull;


int individualParallelTest(NQueen nqueen, map<us, ull> solutionMap) {
    ull subtotal;
    ull total = 0;
    ofstream myfile;
    double genTime, nqueenTime, totalnqueenTime;

    string filename;
    filename = "testsN16/P" + to_string(nqueen.getWorldSize()) + "N" + to_string(nqueen.getN()) + "depth" + to_string(nqueen.getDepth()) + ".txt";
    myfile.open(filename);
    if (nqueen.getMyRank() == 0) {
        myfile << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        myfile << "Number of parallel processes: " << nqueen.getWorldSize() << "\n";
        myfile << "Depth of initial divide: " << nqueen.getDepth() << "\n";
        myfile << "Value of N: " << nqueen.getN() << "\n";
    }

    genTime = MPI_Wtime();
    nqueen.generateArrays("calculatedValues.txt");
    genTime = MPI_Wtime() - genTime;

    vector<vector<us>> worldSizeBoard = nqueen.fileToVector("calculatedValues.txt");

    nqueenTime = MPI_Wtime();
    subtotal = nqueen.runParallel(worldSizeBoard);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    nqueenTime = MPI_Wtime() - nqueenTime;
    MPI_Reduce(&nqueenTime, &totalnqueenTime, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (nqueen.getMyRank() == 0) {
        myfile << "Time to generate inital configuration (sec) = " << genTime << "\n";
        myfile << "Total time from all ranks (sec) = " << totalnqueenTime << "\n";
    }
    if (total == solutionMap[nqueen.getN()]) {
        myfile << "Time to execute on rank " << nqueen.getMyRank() << " (sec) = " << nqueenTime << "\n";
    } 
    else {
        myfile << "Wrong solution calculated" << "\n";
    }
    return total;
}

int noFileParallelTest(NQueen nqueen, string filename, map<us, ull> solutionMap) {
    ull subtotal;
    ull total = 0;

    vector<vector<us>> worldSizeBoard = nqueen.fileToVector(filename);

    subtotal = nqueen.runParallel(worldSizeBoard);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (nqueen.getMyRank() == 0) {
        ofstream myfile;
        myfile.open("testResultsHPC.txt", ios::app);
        if (total == solutionMap[nqueen.getN()]) {
            myfile << 0 << " " << nqueen.getN() << " " << nqueen.getDepth() << " " << nqueen.getWorldSize() << " "; 
        } else {
            myfile << 1 << " " << nqueen.getN() << " " << nqueen.getDepth() << " " << nqueen.getWorldSize() << " "; 
        }
        myfile.close();
    }


    return total;
}

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    // Get the number of processes
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    //Get rank of the processes
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

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

    if (argc == 4) {
        int depth, N;
        string filename;
        N = stoi(argv[1]);
        depth = stoi(argv[2]);
        filename = argv[3];

        NQueen nqueen(N, depth, worldSize, myRank);

        if (nqueen.getMyRank() == 0) {
            cout << nqueen.getN() << " " << nqueen.getDepth() << " " << nqueen.getWorldSize() << endl;
        }

        noFileParallelTest(nqueen, filename, solutionMap);

    }

    MPI_Finalize();

}