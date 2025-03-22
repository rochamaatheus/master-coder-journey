#include <iostream>
using namespace std;

// Códigos ANSI
#define GREEN "\033[32m"
#define RESET "\033[0m"

int board[9][9] = {
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

int original[9][9];

// Imprime a matriz com destaque nos valores adicionados
void printBoard() {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (original[i][j] == 0) {
        cout << GREEN << board[i][j] << RESET << " ";
      } else {
        cout << board[i][j] << " ";
      }
      if ((j + 1) % 3 == 0 && j < 8)
        cout << "| ";
    }
    cout << endl;
    if ((i + 1) % 3 == 0 && i < 8)
      cout << "---------------------" << endl;
  }
}

// Verifica se o número pode ser colocado na posição
bool isValid(int row, int col, int num) {
  for (int i = 0; i < 9; ++i) {
    if (board[row][i] == num || board[i][col] == num)
      return false;
  }

  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[startRow + i][startCol + j] == num)
        return false;
    }
  }

  return true;
}

// Backtracking recursivo
bool solve() {
  for (int row = 0; row < 9; ++row) {
    for (int col = 0; col < 9; ++col) {
      if (board[row][col] == 0) {
        for (int num = 1; num <= 9; ++num) {
          if (isValid(row, col, num)) {
            board[row][col] = num;

            if (solve())
              return true;

            board[row][col] = 0; // Backtrack
          }
        }
        return false;
      }
    }
  }
  return true;
}

int main() {
  // Tabuleiro original
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
      original[i][j] = board[i][j];

  if (solve()) {
    cout << "\n Sudoku Resolvido!\n";
    printBoard();
  } else {
    cout << "Não foi possível resolver o Sudoku.\n";
  }

  return 0;
}