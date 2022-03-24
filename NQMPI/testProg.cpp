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

bool runParallel(int N, int world_size, int my_rank, string filename, int depth) {
	//Calc time to run
	MPI_Barrier(MPI_COMM_WORLD);
	double elapsedTime = -MPI_Wtime();

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

	MPI_Barrier(MPI_COMM_WORLD);
	elapsedTime += MPI_Wtime();

	if (my_rank == 0)
	{
		cout << "Program executed in " << 1000 * elapsedTime << std::endl;
		cout << "Total number of solutions found: " << total << std::endl;
	}

	return true;
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


int main(int argc, char** argv) {
    int num = 0;
    // Initialize the MPI environment
    // Must run before all other MPI commands
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    //Get rank of the processes
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int N = 10;
	int depth = 4;
	//Generate Arrays
	if (my_rank == 0) {
		generateArrays(N, "testValue.txt", depth);
	}
	runParallel(N, world_size, my_rank, "testValue.txt", depth);

    MPI_Finalize();
}



//mpiexec -n <number of processes> ./NQMPI.exe