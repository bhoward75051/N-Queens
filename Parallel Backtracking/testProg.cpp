#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool checkSquare(int N, int x, int y, vector<int> board) {

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

//init y = 0
int nqueens(int N, int y, vector<int> board) {
	int solutions = 0;
	if (y == N) solutions++;
	else {
		for (int i = 0; i < N; i++) 
		{	
			if (checkSquare(N, i, y, board)) 
			{
				board[y] = i;
				solutions += nqueens(N, y + 1, board);
				board[y] = N;
			}
		}
	}

	return solutions;

}

bool printArr(int N, int board[]) {
	cout << "[";
	for (int i = 0; i < N; i++)
	{
		if (i == (N - 1)) {
			cout << board[i];
		}
		else {
			cout << board[i] << ", ";
		}
	}
	cout << "]\n";
	return true;
}

int runParallel(int N, int world_size, int my_rank, string filename, int depth) {

	vector<vector<int>> worldSizeBoard;
	vector<int> oneBoard;
	for (int i = 0; i < N; i++) {
		oneBoard.push_back(N);
	}
	for (int i = 0; i < world_size; i++) {
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
			if (rankCounter == world_size) {
				subtotal += nqueens(N, depth, worldSizeBoard[my_rank]);
				rankCounter = 0;
			}

		}

		myfile.close();
	}

	unsigned long total = 0;
	MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	return subtotal;
}

int nqueensLimitedDepth(int N, int y, vector<int> board, int depth, ofstream &myfile) {
	if (y == depth) {
		for (int i = 0; i < N; i++) 
		{
			myfile << board[i] << " ";
		}
		myfile << "\n";
	}
	else {
		for (int i = 0; i < N; i++) {
			if (checkSquare(N, i, y, board)) 
			{
				board[y] = i;
				nqueensLimitedDepth(N, y + 1, board, depth, myfile);
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
	nqueensLimitedDepth(N, 0, board, depth, myfile);
	myfile.close();

	return true;

}

//mpiexec -n <number of processes> ./NQMPI.exe