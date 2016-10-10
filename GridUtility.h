#pragma once
#include "Board.h"
#include "Cell.h"
#include "Grid.h"
#include "Node.h"
#include <utility>

namespace GridUtility {
  void Print(Board board, const std::vector<std::pair<Coord, Cell>>& extras = {});
  void print(const Grid<NodeBFS>& board);
  void print(const Grid<NodeDFS>& board);
}
