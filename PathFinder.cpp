#include "PathFinder.h"

namespace PathFinder {
  bool IsSequenceValid(const std::vector<Cell>& path, const Piece& piece) {
    if (path.size() < 2)
      throw std::invalid_argument("Path is too short. Cannot compute sequence");

    for (size_t i = 1; i < path.size(); ++i) {
      const Cell start = path[i - 1];
      const Cell end = path[i];
      if (!piece.IsMoveValid(start, end))
        return false;
    }
    return true;
  }
}