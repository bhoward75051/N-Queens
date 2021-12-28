public class Backtracking {
    final int queenGoal = 27;

    public Boolean navigateBoard(int y, Boolean[][] board) {

        if (y >= queenGoal) {
            return true;
        }

        for (int i = queenGoal - 1; i >= 0; i--) {
            if(checkSquare(i, y, board)) {
                board[i][y] = true;

                if (navigateBoard(y + 1, board)) {
                    return true;
                }

                board[i][y] = false;
            }
        }

        return false;

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
         if (navigateBoard(0, board) == false) {
             System.out.println("No solution");
             return false;
         }
        printBoard(board);
        return true;
    }

    public static void main(String args[]) {
        Backtracking NQueens = new Backtracking();
        NQueens.nq();
    }
}
