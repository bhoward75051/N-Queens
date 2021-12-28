#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
constexpr auto N = 14;

bool checkSquare(int x, int y, bool (*arr)[N]) {
	int i, j, kx, ky;

	for (i = -x; i < (-x + N); i++) {
		if (arr[x + i][y]) {
			return false;
		}
	}

	for (j = -y; j < (-y + N); j++) {
		if (arr[x][y + j]) {
			return false;
		}
	}

	for (kx = 0; kx < N; kx++) {
		for (ky = 0; ky < N; ky++) {
			if ((arr[kx][ky]) && ((kx + ky == x + y) || (kx - ky == x - y))) {
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

int navigateBoard(int y, bool (*arr)[N], int solutions) {
	if (y == N)
		//printBoard(arr);
		solutions++;

	for (int i = 0; i < N; i++) {
		if (checkSquare(i, y, arr)) {
			arr[i][y] = true;

			solutions += navigateBoard(y + 1, arr, 0);

			arr[i][y] = false;
		}
	}
	return solutions;
}

bool navigateBoardOnce(int y, bool(*arr)[N]) {
	if (y >= N)
		return true;

	for (int i = N - 1; i >= 0; i--) {
		if (checkSquare(i, y, arr)) {
			arr[i][y] = true;

			if (navigateBoardOnce(y + 1, arr))
				return true;

			arr[i][y] = false;
		}
	}

	return false;
}

bool nq() {
	bool board[N][N];

	memset(board, false, sizeof board);

	cout << "Total solutions for size n ";
	cout << N;
	cout << " is ";
	cout << navigateBoard(0, board, 0);

	//if (navigateBoard(0, board) == false) {
	//	printf("Solution does not exist");
	//	return false;
	//}

	//printBoard(board);
	return true;
}

int main() {	
	nq();
	return 0;
}