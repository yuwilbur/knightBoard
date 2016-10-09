#pragma once
#include "Board.h"
#include "Cell.h"
#include "Grid.h"
#include "Node.h"
#include <utility>

namespace GridUtility {
  void print(const Board& board);
  void print(const Grid<NodeBFS>& board);
}
