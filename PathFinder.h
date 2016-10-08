#pragma once
#include "Piece.h"
#include <vector>

namespace PathFinder {
  bool IsSequenceValid(const std::vector<Coord>& path, const Piece& piece);
  std::vector<Coord> ComputePath(const Board<Cell>& board, const Piece& piece, const Coord& start, const Coord& end);
};