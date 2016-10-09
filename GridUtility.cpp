#include "GridUtility.h"
#include <iostream>

namespace GridUtility {
  void print(const Board& board) {
    auto getLabel = [](const Cell cell) -> char {
      switch (cell) {
      case Cell::Free: return '.';
      case Cell::Water: return 'W';
      case Cell::Rock: return 'R';
      case Cell::Barrier: return 'B';
      case Cell::Teleport: return 'T';
      case Cell::Lava: return 'L';
      case Cell::Knight: return 'K';
      default: throw std::invalid_argument("Cell type is not supported for print");
      }
    };

    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << getLabel(board[Coord(x, y)]) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void print(const Grid<Node>& board) {
    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << board[Coord(x, y)].distance << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}
