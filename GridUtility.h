#pragma once
#include "Board.h"
#include "Cell.h"
#include "Grid.h"

namespace GridUtility {
  void print(const Board& board);
  void print(const Grid<int>& board);
  void print(const Grid<Coord>& board);
}
