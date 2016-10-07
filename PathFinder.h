#pragma once
#include "Piece.h"
#include <vector>

namespace PathFinder {
  bool IsSequenceValid(const std::vector<Cell>& path, const Piece& piece);
};