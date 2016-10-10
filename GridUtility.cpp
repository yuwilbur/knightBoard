#include "GridUtility.h"
#include <iostream>

namespace GridUtility {
  void Print(Board board, const std::vector<std::pair<Coord, Cell>>& extras) {
    auto getLabel = [](const Cell cell) -> char {
      switch (cell) {
      case Cell::Free: return '.';
      case Cell::Start: return 'S';
      case Cell::End: return 'E';
      case Cell::Water: return 'W';
      case Cell::Rock: return 'R';
      case Cell::Barrier: return 'B';
      case Cell::Teleport: return 'T';
      case Cell::Lava: return 'L';
      case Cell::Knight: return 'K';
      default: throw std::invalid_argument("Cell type is not supported for print");
      }
    };

    for (auto& extra : extras) {
      board[extra.first] = extra.second;
    }

    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << getLabel(board[Coord(x, y)]) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void print(const Grid<NodeBFS>& board) {
    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << board[Coord(x, y)].distance << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void print(const Grid<NodeDFS>& board) {
    for (int y = 0; y < (int)board.height; ++y) {
      for (int x = 0; x < (int)board.width; ++x) {
        std::cout << ((board[Coord(x, y)].visited) ? "x" : ".");
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}
