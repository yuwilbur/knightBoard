#pragma once
#include "Board.h"
#include "Cell.h"

namespace BoardUtility {
  void print(const Board<Cell>& board);
  void print(const Board<int>& board);
  void print(const Board<Coord>& board);
}
