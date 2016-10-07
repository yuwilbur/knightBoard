#pragma once
#include <vector>
#include "Cell.h"

class Board {
public:
  Board(const unsigned int width, const unsigned int height);

  Cell Get(const size_t x, const size_t y) const;
  
  void print() const;

private:
  const unsigned int width_;
  const unsigned int height_;
  std::vector<std::vector<Cell::State>> cells_;
};