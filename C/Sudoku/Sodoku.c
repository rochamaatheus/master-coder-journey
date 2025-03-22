#include <stdio.h>

// Códigos ANSI para cor no terminal
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

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

// Cópia do tabuleiro original
int originalBoard[9][9];

// Função para imprimir o tabuleiro com cor nos números adicionados
void printBoard() {
  printf("\nSudoku Resolvido:\n");
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (originalBoard[row][col] == 0) {
        printf(GREEN "%d " RESET, board[row][col]);
      } else {
        printf("%d ", board[row][col]);
      }

      if ((col + 1) % 3 == 0 && col < 8)
        printf("| ");
    }

    printf("\n");
    if ((row + 1) % 3 == 0 && row < 8)
      printf("---------------------\n");
  }
}

// Função para verificar se um número pode ser colocado na posição
int isValid(int row, int col, int num) {
  // Verifica a linha e coluna
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == num || board[i][col] == num) return 0;
  }

  // Verifica o bloco 3x3
  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[startRow + i][startCol + j] == num) return 0;
    }
  }

  return 1;
}

// Função para encontrar uma célula vazia
int findEmptySpot(int *row, int *col) {
  for (*row = 0; *row < 9; (*row)++) {
    for (*col = 0; *col < 9; (*col)++) {
      if (board[*row][*col] == 0) {
        return 1; // Encontrou espaço vazio
      }
    }
  }
  return 0; // Não encontrou espaços vazios
}

// Algoritmo de backtracking para resolver o Sudoku
int solveSudoku() {
  int row, col;
  
  if (!findEmptySpot(&row, &col)) return 1;

  for (int num = 1; num <= 9; num++) {
    if (isValid(row, col, num)) {
      board[row][col] = num; // Tenta colocar um número

      if (solveSudoku()) return 1; // Se resolveu, retorna verdadeiro

      board[row][col] = 0; // Backtracking erro
    }
  }

  return 0;
}

int main() {
  // Copia o tabuleiro original
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      originalBoard[i][j] = board[i][j];
    }
  }

  if (solveSudoku()) {
    printBoard();
  } else {
    printf("Não foi possível resolver o Sudoku.\n");
  }

  return 0;
}
