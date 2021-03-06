//
// Created by Kaahan Motwani on 3/22/20.
//

#include "sudoku/Puzzle.h"
#include "sudoku/solver.h"

string solved_puzzle;

Puzzle::Puzzle() = default;

istream &operator>>(istream& is, Puzzle puzzle) {
  int board[9][9];
  is >> puzzle.game;
  // Loops through puzzle string and replaces all '_' with '0' chars so that the
  // board is all integers for solver.cc's implementation of solving puzzles.
  for (char & i : puzzle.game) {
    if (i == '_') {
      i = '0';
    }
  }

  // This nested for loop loops through the 81 character string and creates
  // a 9x9 board of integers to store the puzzle
  const int kSqrtBoardSize = 9;
  for (size_t row = 0; row < kSqrtBoardSize; row++) {
    for (size_t col = 0; col < kSqrtBoardSize; col++) {
      board[row][col] = (int) (puzzle.game[col + (row * kSqrtBoardSize)]);
      // The following line subtracts '0' in order to get the correct digit
      // based on character encodings.
      board[row][col] -= '0';
    }
  }

  if (sudoku::SolveSudoku(board)) {
    puzzle.game.clear();
    for (auto & row : board) {
      for (int col : row) {
        // This line adds ints to puzzle.game and adds '0' to a casted char
        // to get the correct digit based onc character encodings
        puzzle.game += '0' + static_cast<char>(col);
        solved_puzzle = puzzle.game;
      }
    }
  } else {
    std::istringstream unsolvable("Unsolvable");
    return unsolvable;
  }
  return is;
}

ostream &operator<<(ostream& os, const Puzzle& puzzle) {
  os << solved_puzzle;
  return os;
}


