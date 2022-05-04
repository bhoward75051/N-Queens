#include <string>

#include "NQueen.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 4) {
        string filename;
        int depth, N;
        N = stoi(argv[1]);
        depth = stoi(argv[2]);
        filename = argv[3];

        NQueen nqueen(N, depth, 1, 1);

        nqueen.generateArrays(filename);

    } else {
        cout << "Incorrect number of arguements" << std::endl;
    }
}