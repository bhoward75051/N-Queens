#include <mpi.h>
#include <iostream>

using namespace std;

constexpr auto N = 8;

int testReturn(int my_rank) {
    return my_rank;
}

bool checkSquare(int x, int y, int arr[N]) {

	//Check X axis
	if (arr[y] < N) {
		return false;
	}

	for (int i = 0; i < N; i++) {
		//Check Y axis
		if (arr[i] == x) {
			return false;
		}
		//Check Diagonal
		if (arr[i] < N) {
			if ((i + arr[i] == x + y) || (arr[i] - i == x - y)) {
				return false;
			}
		}
	}

	return true;
}

void printBoard(bool(*arr)[N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}


//init y = 0
int navigateBoard(int y, int arr[N], int solutions) {
	//for (int i = 0; i < N; i++) {
	//	cout << arr[i];
	//}
	//cout << "\n" << std::endl;
	if (y == N) {
		solutions++;
	}
	else {
		for (int i = 0; i < N; i++) {	
			if (checkSquare(i, y, arr)) {
				arr[y] = i;
				solutions += navigateBoard(y + 1, arr, 0);
				arr[y] = N;
			}
		}
	}

	return solutions;

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

	//Calc time to run
	MPI_Barrier(MPI_COMM_WORLD);
	double elapsedTime = -MPI_Wtime();



	int arr[N * N][N] = { {N} };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[(N * i) + j][0] = i;
			arr[(N * i) + j][1] = j;
		}
	}

	int tempArr[N];
	for (int i = 0; i < N; i++) {
		tempArr[i] = N;
	}

	int subtotal = 0;
	/*
	if (my_rank == 0) {
		tempArr[0] = 0;
		subtotal += navigateBoard(1, tempArr, 0);
		tempArr[0] = 1;
		subtotal += navigateBoard(1, tempArr, 0);
	}
	else if (my_rank == 1) {
		tempArr[0] = 2;
		subtotal += navigateBoard(1, tempArr, 0);
		tempArr[0] = 3;
		subtotal += navigateBoard(1, tempArr, 0);
	}
	else if (my_rank == 2) {
		tempArr[0] = 4;
		subtotal += navigateBoard(1, tempArr, 0);
		tempArr[0] = 5;
		subtotal += navigateBoard(1, tempArr, 0);
	}
	else {
		tempArr[0] = 6;
		subtotal += navigateBoard(1, tempArr, 0);
		tempArr[0] = 7;
		subtotal += navigateBoard(1, tempArr, 0);
	} */
	
	for (int x = 0; x < N; x += world_size) {
		tempArr[0] = x + my_rank;
		subtotal += navigateBoard(1, tempArr, 0);
	}

	/*tempArr[0] = 1;
	tempArr[1] = 4;
	cout << navigateBoard(2, tempArr, 0) << std::endl;*/


	unsigned long total = 0;
	MPI_Reduce(&subtotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	elapsedTime += MPI_Wtime();


	if (my_rank == 0) {
		cout << "Program executed in " << 1000 * elapsedTime << std::endl;
		cout << "Total number of solutions found: " << total << std::endl;
	}

    MPI_Finalize();
}



//mpiexec -n <number of processes> ./NQMPI.exe