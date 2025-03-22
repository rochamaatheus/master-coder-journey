import os

# ANSI
GREEN = "\033[32m"
RESET = "\033[0m"

# Tabuleiro Inicial
board = [
  [5, 3, 0, 0, 7, 0, 0, 0, 0],
  [6, 0, 0, 1, 9, 5, 0, 0, 0],
  [0, 9, 8, 0, 0, 0, 0, 6, 0],
  [8, 0, 0, 0, 6, 0, 0, 0, 3],
  [4, 0, 0, 8, 0, 3, 0, 0, 1],
  [7, 0, 0, 0, 2, 0, 0, 0, 6],
  [0, 6, 0, 0, 0, 0, 2, 8, 0],
  [0, 0, 0, 4, 1, 9, 0, 0, 5],
  [0, 0, 0, 0, 8, 0, 0, 7, 9]
]

# Cópia
original = [row.copy() for row in board]

# Printando valores
def print_board():
  for i in range(9):
    for j in range(9):
      num = board[i][j]
      if original[i][j] == 0:
        print(f"{GREEN}{num}{RESET} ", end="")
      else:
        print(f"{num} ", end="")

      if (j + 1) % 3 == 0 and j < 8:
        print("| ", end="")
    print()
    if (i + 1) % 3 == 0 and i < 8:
      print("-" * 21)

# Verifica se pode colocar número
def is_valid(row, col, num):
  if num in board[row]:
    return False
  
  for i in range(9):
    if board[i][col] == num:
      return False
    
  start_row = (row // 3) * 3
  start_col = (col // 3) * 3

  for i in range(3):
    for j in range(3):
      if board[start_row + i][start_col + j] == num:
        return False
  
  return True

# Backtracking
def solve():
  for row in range(9):
    for col in range(9):
      if board[row][col] == 0:
        for num in range(1, 10):
          if is_valid(row, col, num):
            board[row][col] = num
            if solve():
              return True
            board[row][col] = 0
        return False
  return True

# Execução
if solve():
  print("Sudoku resolvido!")
  print_board()
else:
  print("Não foi possível resolver o Sudoku.")
