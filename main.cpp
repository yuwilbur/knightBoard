#include "Board.h"
#include "BoardUtility.h"
#include "Knight.h"
#include "PathFinder.h"
#include <iostream>

int main() {
  std::cout << "START" << std::endl;

  Board<Cell> board(7, 7);
  board.Fill(Cell::Free);
  BoardUtility::print(board);
  std::cout << std::endl;
  
  Knight knight(board);
  Coord start = Coord(5, 5);
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

  auto movesets = knight.GetMoveSet(Coord(1, 1));
  for (auto& moveset : movesets) {
    std::cout << moveset.x << "," << moveset.y << std::endl;
  }
  std::cout << std::endl;

  auto test = PathFinder::ComputePath(board, knight, Coord(2, 3), Coord(4, 1));
  for (size_t i = 0; i < test.size(); ++i) {
    std::cout << test[i].x << "," << test[i].y << " ";
  }
  std::cout << std::endl;

  std::cout << "END" << std::endl;
  system("pause");
  return 0;
}