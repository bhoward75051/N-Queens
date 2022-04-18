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

	void setN(us N_) { N = N_; }

	void setDepth(us depth_) { depth = depth_; }

	void setWorldSize(us worldSize_) { worldSize = worldSize_; }

	void setMyRank(us myRank_) { myRank = myRank_; }

	us getN() { return N; }

	us getDepth() { return depth; }

	us getWorldSize() { return worldSize; }

	us getMyRank() { return myRank; }

	bool checkSquare(us x, us y, vector<us> board) {

		//Check X axis
		if (board[y] < N) return false;

		for (us i = 0; i < N; i++)
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

	ull nqueens(us y, vector<us> board) {
		ull solutions = 0;
		if (y == N) solutions++;
		else {
			for (us i = 0; i < N; i++)
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

	ull runParallel(vector<vector<us>> worldSizeBoard) {
		ull subtotal = 0;
		for (std::vector<vector<us>>::size_type i = 0; i < worldSizeBoard.size(); i+= worldSize) {
			if (i + myRank < worldSizeBoard.size()) {
				subtotal += nqueens(depth, worldSizeBoard[i + myRank]);
			}
		}
		return subtotal;
	}

	vector<us> createBoard(us N) {
		vector<us> board;
		for (us i = 0; i < N; i++) {
			board.push_back(N);
		}
		return board;
	}

	vector<vector<us>> fileToVector(string filename) {
		vector<vector<us>> worldSizeBoard;
		vector<us> oneBoard;
		us counter = 0;
		us i;

		for (us i = 0; i < N; i++) {
			oneBoard.push_back(N);
		}

		ifstream myfile(filename);
		if (myfile.is_open())
		{
			while (myfile >> i)
			{
				oneBoard[counter] = i;
				counter++;
				if (counter == N) {
					counter = 0;
					worldSizeBoard.push_back(oneBoard);
				}
			}
			myfile.close();
		}
		return worldSizeBoard;
	}

	ull runParallelNew(string filename) {
		vector<vector<us>> worldSizeBoard;
		vector<us> oneBoard;
		us counter = 0;

		for (us i = 0; i < N; i++) {
			oneBoard.push_back(N);
		}
		for (us i = 0; i < worldSize; i++) {
			worldSizeBoard.push_back(oneBoard);
		}

		ull subtotal = 0;
		ifstream myfile(filename);

		if (myfile.is_open())
		{
			us counter = 0;
			ull rankCounter = 0;
			us i;
			while (myfile >> i)
			{
				worldSizeBoard[rankCounter][counter] = i;
				oneBoard[counter] = i;
				counter++;
				if (counter == N) {
					counter = 0;
					rankCounter++;
				}
				if (rankCounter == worldSize) {
					subtotal += nqueens(depth, worldSizeBoard[myRank]);
					rankCounter = 0;
					worldSizeBoard.push_back(oneBoard);
				}
			}
			myfile.close();
			return subtotal;
		}
	}

	int nqueensLimitedDepth(us y, vector<us> board, ofstream& myfile) {
		if (y == depth) {
			for (us i = 0; i < N; i++)
			{
				myfile << board[i] << " ";
			}
			myfile << "\n";
		}
		else {
			for (us i = 0; i < N; i++) {
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

	bool generateArrays(string filename) {
		vector<us> board;
		for (us i = 0; i < N; i++)
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