#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

constexpr auto N = 8;

bool checkSquare(int x, int y, int board[N]) {

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
int nqueens(int y, int board[N]) {
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

bool printArr(int board[N]) {
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

bool runParallel(int world_size, int my_rank) {
	//Calc time to run
	MPI_Barrier(MPI_COMM_WORLD);
	double elapsedTime = -MPI_Wtime();

	int board[N];
	for (int i = 0; i < N; i++) 
	{
		board[i] = N;
	}

	int subtotal = 0;

	for (int x = 0; x < N; x += world_size) 
	{
		if (x + my_rank < N) 
		{
			board[0] = x + my_rank;
			subtotal += nqueens(1, board);
		}
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

bool runParallelNew(int world_size, int my_rank, string filename) {
	//Calc time to run
	//MPI_Barrier(MPI_COMM_WORLD);
	//double elapsedTime = -MPI_Wtime();

	int(*fullArray)[N] = new int[world_size][N];
	int subtotal = 0;
	ifstream myfile(filename);

	if (myfile.is_open())
	{
		int counter = 0;
		int rankCounter = 0;
		int i;
		while (myfile >> i)
		{
			fullArray[rankCounter][counter] = i;
			counter++;
			if (counter == N) {
				counter = 0;
				rankCounter++;
			}
			if (rankCounter == world_size) {
				subtotal += nqueens(3, fullArray[my_rank]);
				rankCounter = 0;
			}

		}

		myfile.close();
	}

	unsigned long total = 0;
	MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	//MPI_Barrier(MPI_COMM_WORLD);
	//elapsedTime += MPI_Wtime();


	if (my_rank == 0)
	{
		//cout << "Program executed in " << 1000 * elapsedTime << std::endl;
		cout << "Total number of solutions found: " << total << std::endl;
	}

	return true;
}

int nqueensLimitedDepth(int y, int board[N], int depth, ofstream &myfile) {
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
				nqueensLimitedDepth(y + 1, board, depth, myfile);
				board[y] = N;
			}
		}
	}
	return 0;
}

bool generateArrays(string filename) {
	int board[N];
	for (int i = 0; i < N; i++) 
	{
		board[i] = N;
	}
	ofstream myfile;
	myfile.open(filename);
	nqueensLimitedDepth(0, board, 3, myfile);
	myfile.close();

	return true;

}

/*int getFileLineLength(ifstream& myfile) {
	int count = 0;
	string line;
	while (getline(myfile, line)) count++;
	return count;
}

bool readFileToArray(string filename) {
	string line;
	ifstream myfile(filename);

	int board[N];
	for (int i = 0; i < N; i++)
	{
		board[i] = N;
	}

	int lengthOfArray = getFileLineLength(myfile);
	int completeData[lengthOfArray][N];

	if (myfile.is_open())
	{
		int counter = 0;
		int i;
		while (myfile >> i)
		{
			if (counter == N) {
				printArr(board);
				counter = 0;
			}
			board[counter] = i;
			counter++;

		}
		myfile.close();
		return true;
	}
	else return false;
}*/

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

	//Run Parallel 
	//runParallel(world_size, my_rank);

	//Generate Arrays
	generateArrays("testValue.txt");
	runParallelNew(world_size, my_rank, "testValue.txt");

    MPI_Finalize();
}



//mpiexec -n <number of processes> ./NQMPI.exe