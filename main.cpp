#include<iostream>
#include<time.h>

using namespace std;
constexpr auto N = 14;

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


//init y = 0
int navigateBoard(int y, int arr[N], int solutions) {
	if (y == N)
		solutions++;

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

bool nq() {
	int arr[N];
	for (int i = 0; i < N; i++) {
		arr[i] = N;
	}

	cout << "Total solutions for size n " << N << " is " << navigateBoard(0, arr, 0);

	return true;
}

int main() {
	clock_t tStart = clock();
	nq();
	printf("\nTime taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}