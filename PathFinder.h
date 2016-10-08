#pragma once
#include "Piece.h"
#include <vector>

namespace PathFinder {
  std::vector<Coord> ComputePath(const Board& board, const Piece& piece, const Coord& start, const Coord& end);
};