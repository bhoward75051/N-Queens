#include <mpi.h>
#include <stdio.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <bitset>
#include <vector>
#include <map>

using namespace std;

int boardSize, mask, total, depth;

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
        {16, 14772512},
        {17, 95815104},
        {18, 666090624},
        {19, 4968057848},
        {20, 39029188884},
        {21, 314666222712}
    };

void Nqueen(int y, int left, int down, int right) {
    int bitmap, bit;

    if (y == boardSize) {
        total++;
    } else {
        bitmap = mask & ~(left | down | right);
        while (bitmap) { //While any int is not 0. 
            bit = -bitmap & bitmap;
            bitmap ^= bit;
            Nqueen(y+1, (left | bit) << 1, down | bit, (right | bit) >> 1);
        }
    }

}

vector<vector<int>> fileToVector(string filename) {
		vector<vector<int>> fullValues;
		vector<int> values;
		int counter = 0;
	    int i;

		for (i = 0; i < 4; i++) {
			values.push_back(0);
		}

		ifstream myfile(filename);
		if (myfile.is_open())
		{
			while (myfile >> i)
			{
				values[counter] = i;
				counter++;
				if (counter == 4) {
					counter = 0;
					fullValues.push_back(values);
				}
			}
			myfile.close();
		}
		return fullValues;
	}

void parallelTest(vector<vector<int>> fullValues, int worldSize, int myRank) {
	for (vector<vector<int>>::size_type i = 0; i < fullValues.size(); i+= worldSize) {
		if (i + myRank < fullValues.size()) {
			Nqueen(fullValues[i + myRank][0], fullValues[i + myRank][1], fullValues[i + myRank][2], fullValues[i + myRank][3]);
		}
	}
}


int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    // Get the number of processes
    int worldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);

    //Get rank of the processes
    int myRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    if (argc != 3) {
        cout << "Not enough args" << endl;
        return 0;
    }

    boardSize = atoi(argv[1]);
    depth = atoi(argv[2]);
    total = 0;
    mask = (1 << boardSize) - 1;

    int completeTotal;

    vector<vector<int>> fullValues = fileToVector("depthValues.txt");
    parallelTest(fullValues, worldSize, myRank);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&total, &completeTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myRank == 0) {
        ofstream myfile;
        myfile.open("testResultsBitHPC.txt", ios::app);
        if (completeTotal == solutionMap[boardSize]) {
            myfile << 0 << " " << boardSize << " " << depth << " " << worldSize << " "; 
        } else {
            myfile << 1 << " " << boardSize << " " << depth << " " << worldSize << " "; 
        }
        myfile.close();
    }

    MPI_Finalize();

    return 0;
}
