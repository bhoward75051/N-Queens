/* 
* This is heavily based of Jeff Somers program 
* http://users.rcn.com/liusomers/nqueen_demo/nqueens.html
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

int boardSize, mask, total;

void Nqueen(int y, int left, int down, int right) {
    int bitmap, bit;

    if (y == boardSize) {
        total++;
    } else {
        bitmap = mask & ~(left | down | right);
        while (bitmap) {
            bit = -bitmap & bitmap;
            bitmap ^= bit;
            Nqueen(y+1, (left | bit) << 1, down | bit, (right | bit) >> 1);
        }
    }

}


int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Not enough args" << endl;
        return 0;
    }

    boardSize = atoi(argv[1]);
    total = 0;
    mask = (1 << boardSize) - 1;

    Nqueen(0, 0, 0, 0); 

    cout << total << endl;;
    return 0;
}