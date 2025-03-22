package Desafios.Java.Sudoku;

public class Sudoku {
  static int[][] board = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
  };

  static int[][] original = new int[9][9];

  // ANSI Cores
  static final String GREEN = "\u001B[32m";
  static final String RESET = "\u001B[0m";

  public static void main(String[] args) {
    // Copia do tabuleiro original
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        original[i][j] = board[i][j];
      }
    }

    if (solve()) {
      System.out.println("Sudoku Resolvido:\n");
      printBoard();
    } else {
      System.out.println("Não foi possível resolver o Sudoku.");
    }
  }

  static void printBoard() {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (original[i][j] == 0) {
          System.out.print(GREEN + board[i][j] + RESET + " ");
        } else {
          System.out.print(board[i][j] + " ");
        }

        // Divisor visual entre blocos
        if ((j + 1) % 3 == 0 && j < 8) System.out.print("| ");
      }
      System.out.println();

      // Linha horizontal entre blocos
      if ((i + 1) % 3 == 0 && i < 8) {
        System.out.println("---------------------");
      }
    }
  }

  static boolean solve() {
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        if (board[row][col] == 0) {
          for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
              board[row][col] = num;

              if (solve())
                return true;

              board[row][col] = 0; // backtrack
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  static boolean isValid(int row, int col, int num) {
    // Linha e Coluna
    for (int i = 0; i < 9; i++) {
      if (board[row][i] == num || board[i][col] == num)
        return false;
    }

    // Bloco 3x3
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[startRow + i][startCol + j] == num)
          return false;
      }
    }

    return true;
  }
}