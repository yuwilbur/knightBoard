#include "Board.h"
#include "BoardUtility.h"
#include "Knight.h"
#include "PathFinder.h"
#include <iostream>

void Level1() {
  Board<Cell> board(7, 7);
  board.Fill(Cell::Free);
  BoardUtility::print(board);
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
  std::cout << PathFinder::IsSequenceValid(path, knight) << std::endl;
  std::cout << std::endl;

  auto movesets = knight.GetMoveSet(Coord(1, 3));
  for (auto& moveset : movesets) {
    std::cout << moveset.x << "," << moveset.y << std::endl;
  }
  std::cout << std::endl;
}

void Level2() {
  Board<Cell> board(7, 7);
  board.Fill(Cell::Free);
  Knight knight(board);

  auto test = PathFinder::ComputePath(board, knight, Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;
}

void Level3() {
  Board<Cell> board(7, 7);
  board.Fill(Cell::Free);
  Knight knight(board);

  for (int i = 0; i < 7; ++i) {
    for (int j = 4; j < 5; j++) {
      board[Coord(i, j)] = Cell::Rock;
    }
  }
  BoardUtility::print(board);
  std::cout << std::endl;

  auto test = PathFinder::ComputePath(board, knight, Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;
}

void Level4() {

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
  Level3();
  //Level4();
  //Level5();
  //TestCoord();

  system("pause");
  return 0;
}