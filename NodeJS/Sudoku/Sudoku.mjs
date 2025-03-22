import chalk from 'chalk';

const board = [
  [0, 0, 0, 4, 0, 7, 0, 0, 0],
  [0, 0, 8, 0, 6, 0, 4, 0, 0],
  [0, 4, 0, 3, 8, 1, 0, 9, 0],
  [2, 0, 7, 0, 0, 0, 8, 0, 9],
  [0, 5, 9, 0, 0, 0, 6, 1, 0],
  [4, 0, 1, 0, 0, 0, 2, 0, 3],
  [0, 1, 0, 5, 7, 2, 0, 8, 0],
  [0, 0, 3, 0, 1, 0, 5, 0, 0],
  [0, 0, 0, 6, 0, 4, 0, 0, 0],
];

// Cópia do tabuleiro
const originalBoard = board.map(row => [...row]);

// Função para imprimir o tabuleiro
function printBoard(board, originalBoard) {
  for (let row = 0; row < 9; row++) {
    for (let col = 0; col < 9; col++) {
      const num = board[row][col];

      const output =
        originalBoard[row][col] === 0 ? chalk.green(num + ' ') : num + ' ';

      process.stdout.write(output);

      if ((col + 1) % 3 === 0 && col < 8) {
        process.stdout.write('| ');
      }
    }

    console.log(); // <-- quebra a linha no fim da linha
    if ((row + 1) % 3 === 0 && row < 8) {
      console.log('---------------------');
    }
  }
}

// 1. Encontrar um espaço vazio no tabuleiro
function findEmptySpot(board) {
  for (let row = 0; row < 9; row++) {
    for (let col = 0; col < 9; col++) {
      if (board[row][col] == 0) {
        return [row, col];
      }
    }
  }
  return null; // Caso não haja espaços vazios
}

// 2. Verificar se um número pode ser colocado em uma célula
function isValid(board, row, col, num) {
  // Verifica a linha
  if (board[row].includes(num)) return false;

  // Verifica a coluna
  for (let i = 0; i < 9; i++) {
    if (board[i][col] === num) return false;
  }

  // Verifica o bloco 3x3
  const startRow = Math.floor(row / 3) * 3;
  const startCol = Math.floor(col / 3) * 3;
  for (let i = 0; i < 3; i++) {
    for (let j = 0; j < 3; j++) {
      if (board[startRow + i][startCol + j] === num) return false;
    }
  }

  return true;
}

// 3. Resolver o Sudoku com backtracking
function solveSudoku(board) {
  const emptySpot = findEmptySpot(board);
  if (!emptySpot) return true; // Sudoku está resolvido

  const [row, col] = emptySpot;

  for (let num = 1; num <= 9; num++) {
    if (isValid(board, row, col, num)) {
      board[row][col] = num; // Tenta colocar o número válido

      if (solveSudoku(board)) {
        return true; // Tabuleiro resolvido
      }

      board[row][col] = 0; // Voltar atrás
    }
  }

  return false; // Sudoku mal feito
}

// Chamar função para resolver Sudoku
if (solveSudoku(board)) {
  console.log('Sudoku Resolvido!');
  printBoard(board, originalBoard);
} else {
  console.log('Não foi possível resolver o Sudoku');
}
