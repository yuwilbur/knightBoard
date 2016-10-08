#include "BoardUtility.h"
#include <iostream>

namespace BoardUtility {
  void print(const Board<Cell>& board) {
    auto getLabel = [](const Cell cell) -> char {
      switch (cell) {
      case Cell::Free: return '.';
      case Cell::Water: return 'W';
      case Cell::Rock: return 'R';
      case Cell::Barrier: return 'B';
      case Cell::Teleport: return 'T';
      case Cell::Lava: return 'L';
      default: throw std::invalid_argument("Cell type is not supported for print");
      }
    };

    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << getLabel(board.At(Coord(x, y))) << " ";
      }
      std::cout << std::endl;
    }
  }
}
