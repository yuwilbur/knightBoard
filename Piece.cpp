#include "Piece.h"

bool Piece::IsSequenceValid(const std::vector<Coord>& path) const {
  if (path.size() < 2)
    throw std::invalid_argument("Path is too short. Cannot compute sequence");
  for (size_t i = 0; i < path.size(); ++i) {
    if (!IsMoveValid(path[i], path[i - 1]))
      return false;
  }
  return true;
}
