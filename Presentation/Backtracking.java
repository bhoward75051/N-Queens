public class Backt  racking {
    final int queenGoal = 16;

    public Boolean navigateBoardOnce(int y, Boolean[][] board) {

        if (y >= queenGoal) {
            return true;
        }

        for (int i = queenGoal - 1; i >= 0; i--) {
            if(checkSquare(i, y, board)) {
                board[i][y] = true;

                if (navigateBoardOnce(y + 1, board)) {
                    return true;
                }

                board[i][y] = false;
            }
        }

        return false;

    }

    public int navigateBoard(int y, Boolean[][] board, int solutions) {
        if (y == queenGoal) {
            solutions++;
        }

        for (int i = 0; i < queenGoal; i++) {
            if(y < queenGoal) {
                if(checkSquare(i, y, board)) {
                    board[i][y] = true;

                    solutions += navigateBoard(y + 1, board, 0);

                    board[i][y] = false;
                }
            }
        }
        return solutions;
    }

    public Boolean checkSquare(int x, int y, Boolean[][] board) {

        //Checking along the x axis
        for (int i = -x;i < (-x + queenGoal); i++) {
            //System.out.println(y + " " + (x + i));
            if (board[x + i][y]) {
                return false;
            }
        }

        //checking along the y axis
        for (int j = -y; j < (-y + queenGoal); j++) {
            if (board[x][y + j]) {
                return false;
            }
        }

        //checking all diagonals using the fact that all diagonals add up to be the same value
        for (int kx = 0; kx < queenGoal; kx++) {
            for (int ky = 0; ky < queenGoal; ky++) {
                if((board[kx][ky]) && ((kx + ky == x + y) || (kx - ky == x - y))) {
                    return false;
                }
            }
        }

        return true;
    }

    public void printBoard(Boolean[][] board) {
        for (int i = 0; i < queenGoal; i++) {
            for (int j = 0; j < queenGoal; j++) {
                if (board[i][j]) {
                    System.out.print(" Q ");
                } else {
                    System.out.print(" _ ");
                }
            }
            System.out.println();
        }
    }

    public Boolean nq() {
        Boolean[][] board = new Boolean[queenGoal][queenGoal];
        for (int i = 0; i < queenGoal; i++) {
            for (int j = 0; j < queenGoal; j++) {
                board[i][j] = false;
            }
        }
        int solutions = navigateBoard(0, board, 0);
         if (solutions == 0) {
             System.out.println("No solution");
             return false;
         }
        System.out.println("For " + queenGoal + " board size there are " + solutions + " solutions");
        return true;
    }

    public static void main(String args[]) {
        long startTime = System.nanoTime();
        Backtracking NQueens = new Backtracking();
        NQueens.nq();
        long endTime = System.nanoTime();

        long duration = (endTime - startTime);
        double elapsedTimeSeconds = (double) duration / 1000000000;
        System.out.println(elapsedTimeSeconds + " seconds");
    }
}
