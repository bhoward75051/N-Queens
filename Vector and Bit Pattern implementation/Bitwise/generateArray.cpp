#include <stdio.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <bitset>

using namespace std;

int boardSize, mask;

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

int main(int argc, char** argv) {

    if (argc != 3) {
        cout << "Not enough args" << endl;
        return 0;
    }

    boardSize = atoi(argv[1]);
    int depth = atoi(argv[2]);
    mask = (1 << boardSize) - 1;
    
    ofstream myfile;
	myfile.open("depthValues.txt");
	NqueensLimitedDepth(0, 0, 0, 0, depth, myfile);
	myfile.close();

    return 0;
}