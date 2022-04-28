/* TO DO
 * Create a header class with a class for this 
 * Vars will be y, left, down, right, bitmap, mask
 * 
 * Implement MPI 
 * 
 * Explain code
 */


#include <mpi.h>
#include <stdio.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <bitset>
#include <vector>

using namespace std;

int boardSize, mask, total;

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

void NqueensLimitedDepth(int y, int left, int down, int right, int depth, ofstream& myfile) {
    int bitmap, bit;

    if (y == depth) {
        myfile << y << " " << left << " " << down << " " << right << "\n";   
    } else {
        bitmap = mask & ~(left | down | right);
        while (bitmap) { //While any int is not 0.
            bit = -bitmap & bitmap;
            bitmap ^= bit;
            NqueensLimitedDepth(y+1, (left | bit) << 1, down | bit, (right | bit) >> 1, depth, myfile);
        }
    }

}

void generateArrays(string filename, int depth) {
		ofstream myfile;
		myfile.open(filename);
		NqueensLimitedDepth(0, 0, 0, 0, depth, myfile);
		myfile.close();
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

int parallelTest(vector<vector<int>> fullValues, int worldSize, int myRank) {
    int subtotal;
    int total = 0;;
	for (vector<vector<int>>::size_type i = 0; i < fullValues.size(); i+= worldSize) {
		if (i + myRank < fullValues.size()) {
			Nqueen(fullValues[i + myRank][0], fullValues[i + myRank][1], fullValues[i + myRank][2], fullValues[i + myRank][3]);
		}
	}
    //MPI_Barrier(MPI_COMM_WORLD);
    //MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

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
    if (argc != 2) {
        cout << "Not enough args" << endl;
        return 0;
    }

    boardSize = atoi(argv[1]);
    total = 0;
    mask = (1 << boardSize) - 1;

    generateArrays("bitmapNQtest.txt", 3);
    vector<vector<int>> fullValues = fileToVector("bitmapNQtest.txt");
    parallelTest(fullValues, worldSize, myRank);
    cout << total << endl;

    return 0;
}