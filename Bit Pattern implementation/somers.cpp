/* 
* This is heavily based of Jeff Somers program 
* http://users.rcn.com/liusomers/nqueen_demo/nqueens.html
*/

#include <string>
#include <iostream>

using namespace std;

typedef unsigned long ul;
const int MINBOARDSIZE = 2;
const int MAXBOARDSIZE = 18;

ul numberOfSol = 0;

void Nqueen(int boardSize) {
    int nQueenBitRes[MAXBOARDSIZE]; //Results
    int nQueenBitCol[MAXBOARDSIZE]; //Marks columns with queens
    int nQueenPosDiag[MAXBOARDSIZE]; //marks positive diagonals with queens
    int nQueenNegDiag[MAXBOARDSIZE]; //Marks negative diagonals with queens
    int nStack[MAXBOARDSIZE + 2];
    int* pnStack;

    int numrows = 0;
    unsigned int lsb; //Least significant bit
    unsigned int bitfield; //bits which are a set mark possible positions for a queen
    int i;
    int odd = boardSize & 1; //0 if boardSize is even, 1 for odd
    int boardMinus = boardSize - 1; 
    int mask = (1 << boardSize) -1; //if board size is N, mask consists of N 1's

    nStack[0] = -1; //set senital (end of stack)

    for (i = 0; i < (1 + odd); i++) {
        bitfield = 0;
        if (i == 0) { //Not an odd board size
            int half = boardSize>>1; //Half of board size
            bitfield = (1 << half) -1;
            pnStack = nStack + 1;

            nQueenBitRes[0] = 0;
            nQueenBitCol[0] = nQueenPosDiag[0] = nQueenNegDiag[0] = 0;
        }
        else { //Odd board size
            bitfield = 1 << (boardSize >> 1);
            numrows = 1;

            nQueenBitRes[0] = bitfield;
            nQueenBitCol[0] = nQueenPosDiag[0] = nQueenNegDiag[0] = 0;
            nQueenBitCol[1] = bitfield;

            nQueenNegDiag[1] = (bitfield >> 1);
            nQueenPosDiag[1] = (bitfield << 1);
            pnStack = nStack + 1;
            *pnStack++ = 0; 
            bitfield = (bitfield - 1) >> 1;
        }

        for (;;) { //Loop until senital is hit
            lsb = -((signed)bitfield) & bitfield;
            if (bitfield == 0) {
                bitfield = *--pnStack; //Get the previous bitfield from the stack
                if (pnStack == nStack) { //Senital is hit, so we break the loop
                    break;
                }
                --numrows;
                continue;
            }
            bitfield &= ~lsb; //Removes the lsb

            nQueenBitRes[numrows] = lsb;
            if (numrows < boardMinus) {
                int n = numrows++;
                nQueenBitCol[numrows] = nQueenBitCol[n] | lsb;
                nQueenNegDiag[numrows] = (nQueenNegDiag[n] | lsb) >> 1;
                nQueenPosDiag[numrows] = (nQueenPosDiag[n] | lsb) << 1;
                *pnStack++ = bitfield;
                bitfield = mask & ~(nQueenBitCol[numrows] | nQueenNegDiag[numrows] | nQueenPosDiag[numrows]);
                continue;
            }
            else { //If numRows and boardMinus are equal, then a solution is found 
                ++numberOfSol;
                bitfield = *--pnStack;
                --numrows;
                continue;
            }
        }
    }
    numberOfSol *= 2;
}

int main(int argc, char** argv) {
    int boardSize;

    if (argc != 2) {
        cout << "Not enough args" << endl;
        return 0;
    }

    boardSize = atoi(argv[1]);
    if (MINBOARDSIZE > boardSize || MAXBOARDSIZE < boardSize) {
        cout << "Incorrect Board Size" << endl;
        return 0;
    }

    Nqueen(boardSize); 

    cout << numberOfSol << endl;;
}