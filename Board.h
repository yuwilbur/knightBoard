#pragma once
#include <vector>
#include "Cell.h"
#include "Coord.h"

class Board {
public:
  Board(const unsigned int width, const unsigned int height);

  Cell& At(const Coord& coord);

  bool IsValid(const Coord& coord) const;
  
  void print() const;

private:
  const unsigned int width_;
  const unsigned int height_;
  std::vector<std::vector<Cell>> cells_;
};