#pragma once
#include "Cell.h"

class Piece {
public:
  virtual bool IsMoveValid(const Cell& start, const Cell& end) = 0;
};
