#include "Grid.h"
#include "Board.h"
#include "GridUtility.h"
#include "Knight.h"

#include <iostream>

Board ConstructBoard(const std::vector<std::vector<Cell>>& cells) {
  if (cells.size() == 0)
    return Board(0, 0);
  Board board(cells[0].size(), cells.size());
  for (size_t y = 0; y < cells.size(); ++y) {
    for (size_t x = 0; x < cells[y].size(); ++x) {
      board[Coord(x, y)] = cells[y][x];
    }
  }
  board.Setup();
  return board;
}

Board ConstructEasyBoard() {
  using namespace CellAbbreviations;
  const std::vector<std::vector<Cell>> cells = {
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o }
  };
  return ConstructBoard(cells);
}

Board ConstructHardBoard() {
  using namespace CellAbbreviations;
  const std::vector<std::vector<Cell>> cells = {
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, o, o, o, L, L, L, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, o, o, L, L, L, o, o, o, R, R, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, L, L, L, L, L, o, o, o, R, R, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, L, L, L, L, L, L, o, o, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o, R, R, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, B, B, o, o, o, o, o, o, o, o, o, o, o, R, R, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, W, B, B, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, R, R, o, o, o, W, W, B, B, B, B, B, B, B, B, B, B, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, R, R, o, o, o, W, W, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, W, W, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, T, o, o, o, o, o },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, o, o, o, o, B, o, o, R, R, o, o, o, o, o, o, o, o },
    { o, o, o, W, W, o, o, o, o, o, o, o, o, o, o, B, B, B, B, B, o, o, R, R, o, W, W, W, W, W, W, W },
    { o, o, o, W, W, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, W, o, o, o, o, o, o },
    { W, W, W, W, o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, o },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o, B, B, B, B },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, B, B, B, o, o, o, o, o, o, o, o, o, o, B, o, o, o },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, o, o, B, W, W, W, W, W, W, B, B, B, B, B, o, o, o },
    { o, o, o, W, W, W, W, W, W, W, o, o, o, o, o, o, o, B, W, W, W, W, W, W, B, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, o, o, o, B, B, B, o, o, o, o, o, o, o, o, o, o, B, B, o, o, o, o, o, o },
    { o, o, o, o, o, R, R, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o },
    { o, o, o, o, o, R, R, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, o, o, o, B, o, T, o, o, o, o },
    { o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, R, R, o, o, o, o, o, o, B, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, R, R, o, o, o, o, o, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, R, R, o, o, o, o, o, o, o, o },
    { o, o, o, o, o, o, o, o, o, o, o, B, o, o, o, o, o, o, o, o, o, o, R, R, o, o, o, o, o, o, o, o }
  };
  return ConstructBoard(cells);
}

void Level1() {
  std::cout << "Level1" << std::endl;
  // Write a function that accepts a sequence of moves and reports
  // whether the sequence contains only valid knight moves. It should also
  // optionally print the state of the knight board to the terminal as shown
  // above after each move.The current position should be marked with a 'K'.

  Board board = ConstructEasyBoard();
  Knight knight(board);
  Coord start = Coord(1, 3);
  for (size_t y = 0; y < 7; ++y) {
    for (size_t x = 0; x < 7; ++x) {
      Coord end(x, y);
      std::cout << (knight.IsMoveValid(start, end) ? '1' : '.') << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::vector<Coord> path;
  path.push_back(Coord(2, 2));
  path.push_back(Coord(3, 4));
  path.push_back(Coord(2, 2));
  path.push_back(Coord(1, 0));
  std::cout << knight.IsSequenceValid(path) << std::endl;
  std::cout << std::endl;
}

void Level2() {
  std::cout << "Level2" << std::endl;
  // Compute a valid sequence of moves from a given start point to a given end point.

  Board board = ConstructEasyBoard();
  Knight knight(board);

  auto test = knight.ComputeShortestPath(Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;
}

void Level3() {
  std::cout << "Level3" << std::endl;
  //  Compute a valid sequence of moves from a given start point to a
  // given end point in the fewest number of moves.

  Board board = ConstructEasyBoard();
  Knight knight(board);

  for (int i = 0; i < 7; ++i) {
    for (int j = 4; j < 5; j++) {
      board[Coord(i, j)] = Cell::Rock;
    }
  }
  GridUtility::print(board);
  std::cout << std::endl;

  auto test = knight.ComputeShortestPath(Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;
}

void Level4() {
  std::cout << "Level4" << std::endl;
  //  Now repeat the Level 3 task for this 32x32 board. Also, modify
  //  your validator from Level 1 to check your solutions. This board has the
  //  following additional rules :
  //    1) W[ater] squares count as two moves when a piece lands there
  //    2) R[ock] squares cannot be used
  //    3) B[arrier] squares cannot be used AND cannot lie in the path
  //    4) T[eleport] squares instantly move you from one T to the other in the same move
  //    5) L[ava] squares count as five moves when a piece lands there

  Board board = ConstructHardBoard();
  Knight knight(board);
  knight.ComputeShortestPath(Coord(0, 0), Coord(31, 31));
}

void Level5() {
  std::cout << "Level5" << std::endl;
  //  Compute the longest sequence of moves to complete Level 3 without
  //  visiting the same square twice.Use the 32x32 board.

  Board board(4, 4);
  Knight knight(board);
  knight.ComputeLongestPath(Coord(0, 0), Coord(3, 3));
}

int main() {
  Level1();
  Level2();
  Level3();
  Level4();
  Level5();
  return 0;
}