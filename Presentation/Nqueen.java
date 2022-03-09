public class Nqueen {
    final int N = 14;

    public Boolean navigateBoardOnce(int y, int[] board) {

        if (y >= N) {
            return true;
        }

        for (int i = N - 1; i >= 0; i--) {
            if(checkSquare(i, y, board)) {
                board[y] = i;
                if (navigateBoardOnce(y + 1, board)) {
                    return true;
                }
                board[y] = N;
            }
        }
        return false;
    }

    public int navigateBoard(int y, int[] board, int solutions) {

        if (y == N) {
            solutions++;
        }

        for (int i = 0; i < N; i++) {
            if (y < N) {
                if(checkSquare(i, y, board)) {
                    board[y] = i;
                    solutions += navigateBoard(y + 1, board, 0);
                    board[y] = N;
                }
            }
        }
        return solutions;
    }



    public Boolean checkSquare(int x, int y, int[] board) {

        //Checking along the x axis
        if (board[y] < N) {
            return false;
        }

        for (int kx = 0; kx < N; kx++) {
            //Check y axis
            if (board[kx] == x) {
                return false;
            }
            //Check D
            if (board[kx] < N) {
                if((kx + board[kx] == x + y) || (board[kx] - kx  == x - y)) {
                    return false;
                }
            }
        }

        return true;
    }

    public void printBoard(int[] board) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i] == j) {
                    System.out.print(" Q ");
                } else {
                    System.out.print(" _ ");
                }
            }
            System.out.println();
        }
    }

    public Boolean nq() {

        int[] board = new int[N];
        for (int i = 0; i < N; i++) {
            board[i] = N;
        }

        System.out.println(navigateBoard(0, board, 0));
        return true;
        // int[] board = new int[]{2, 4, 4, 4};
        // printBoard(board);
        // checkSquare(3, 1, board);
        // return true;
    }

    public static void main(String args[]) {
        long startTime = System.nanoTime();
        Nqueen NQueens = new Nqueen();
        NQueens.nq();
        long endTime = System.nanoTime();

        long duration = (endTime - startTime);
        double elapsedTimeSeconds = (double) duration / 1000000000;
        System.out.println(elapsedTimeSeconds + " seconds");
    }
}
