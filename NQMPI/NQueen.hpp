#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned short us;
typedef unsigned long long ull;

class NQueen {
private:
	us N;
	us depth;
	us worldSize;
	us myRank;
	
public:

	NQueen(us N_, us depth_, us worldSize_, us myRank_) {
		N = N_;
		depth = depth_;
		worldSize = worldSize_;
		myRank = myRank_;
	}

	bool checkSquare(int x, int y, vector<int> board) {

		//Check X axis
		if (board[y] < N) return false;

		for (int i = 0; i < N; i++)
		{
			//Check Y axis
			if (board[i] == x) return false;

			//Check Diagonal
			if (board[i] < N)
			{
				if ((i + board[i] == x + y) || (board[i] - i == x - y)) return false;
			}
		}
		return true;
	}

	int nqueens(int y, vector<int> board) {
		int solutions = 0;
		if (y == N) solutions++;
		else {
			for (int i = 0; i < N; i++)
			{
				if (checkSquare(i, y, board))
				{
					board[y] = i;
					solutions += nqueens(y + 1, board);
					board[y] = N;
				}
			}
		}

		return solutions;

	}

	int runParallel(string filename) {
		vector<vector<int>> worldSizeBoard;
		vector<int> oneBoard;
		for (int i = 0; i < N; i++) {
			oneBoard.push_back(N);
		}
		for (int i = 0; i < worldSize; i++) {
			worldSizeBoard.push_back(oneBoard);
		}

		int subtotal = 0;
		ifstream myfile(filename);

		if (myfile.is_open())
		{
			int counter = 0;
			int rankCounter = 0;
			int i;
			while (myfile >> i)
			{
				worldSizeBoard[rankCounter][counter] = i;
				counter++;
				if (counter == N) {
					counter = 0;
					rankCounter++;
				}
				if (rankCounter == worldSize) {
					subtotal += nqueens(depth, worldSizeBoard[myRank]);
					rankCounter = 0;
				}

			}
			myfile.close();
		}

		unsigned long total = 0;
		MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		return subtotal;
	}

	int nqueensLimitedDepth(int y, vector<int> board, ofstream& myfile) {
		if (y == depth) {
			for (int i = 0; i < N; i++)
			{
				myfile << board[i] << " ";
			}
			myfile << "\n";
		}
		else {
			for (int i = 0; i < N; i++) {
				if (checkSquare(i, y, board))
				{
					board[y] = i;
					nqueensLimitedDepth(y + 1, board, myfile);
					board[y] = N;
				}
			}
		}
		return 0;
	}

	bool generateArrays(int N, string filename, int depth) {
		vector<int> board;
		for (int i = 0; i < N; i++)
		{
			board.push_back(N);
		}
		ofstream myfile;
		myfile.open(filename);
		nqueensLimitedDepth(0, board, myfile);
		myfile.close();

		return true;
	}
};