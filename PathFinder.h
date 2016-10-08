#pragma once
#include "Piece.h"
#include <vector>

namespace PathFinder {
  bool IsSequenceValid(const std::vector<Coord>& path, const Piece& piece);
  std::vector<Coord> ComputePath(Board board, const Piece& piece, const Coord& start, const Coord& end);
};