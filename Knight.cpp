#include "Knight.h"
#include <cmath>
#include <iostream>

bool Knight::IsMoveValid(const Cell& start, const Cell& end) {
  if (std::abs(start.x - end.x) == 1 && std::abs(start.y - end.y) == 2)
    return true;
  if (std::abs(start.x - end.x) == 2 && std::abs(start.y - end.y) == 1)
    return true;
  return false;
}