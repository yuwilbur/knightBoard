#include "Grid.h"
#include "Board.h"
#include "GridUtility.h"
#include "Knight.h"

#include <iostream>

Board ConstructBoard() {
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

  Board board(32, 32);
  for (size_t y = 0; y < cells.size(); ++y) {
    for (size_t x = 0; x < cells[y].size(); ++x) {
      board[Coord(x, y)] = cells[y][x];
    }
  }
  board.ConstructTeleportEndpoints();
  return board;
}

void Level1() {
  Board board(7, 7);
  board.Fill(Cell::Free);
  GridUtility::print(board);
  std::cout << std::endl;

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

  auto movesets = knight.GetMoveSet(Coord(1, 3));
  for (auto& moveset : movesets) {
    std::cout << moveset.x << "," << moveset.y << std::endl;
  }
  std::cout << std::endl;
}

void Level2() {
  Board board(7, 7);
  board.Fill(Cell::Free);
  Knight knight(board);

  auto test = knight.ComputeShortestPath(Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;

  board[Coord(2, 1)] = Cell::Barrier;
  std::cout << knight.IsMoveValid(Coord(1, 1), Coord(3, 2)) << std::endl;
  std::cout << knight.IsMoveValid(Coord(0, 1), Coord(2, 2)) << std::endl;
  std::cout << knight.IsMoveValid(Coord(0, 0), Coord(2, 1)) << std::endl;
  std::cout << knight.IsMoveValid(Coord(0, 1), Coord(1, 3)) << std::endl;

}

void Level3() {
  Board board(7, 7);
  board.Fill(Cell::Free);
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
  Board board = ConstructBoard();
  Knight knight(board);
  //GridUtility::print(board);
  knight.ComputeShortestPath(Coord(0, 0), Coord(31, 31));
}

void Level5() {

}

void TestCoord() {
  Coord coord1(1, 1);
  Coord coord2(2, 2);
  auto result1 = coord1 + coord2;
  auto result2 = coord2 - coord1;

  std::cout << result1.x << " " << result1.y << std::endl;
  std::cout << result2.x << " " << result2.y << std::endl;

}

int main() {
  //Level1();
  //Level2();
  //Level3();
  Level4();
  //Level5();
  //TestCoord();

  system("pause");
  return 0;
}