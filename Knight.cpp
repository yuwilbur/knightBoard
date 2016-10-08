#include "Knight.h"
#include <cmath>

int Knight::GetDistance(const Coord& start, const Coord& end) const {
  return std::abs(start.x - end.x) + std::abs(start.y - end.y);
}

bool Knight::IsMoveValid(const Coord& start, const Coord& end) const {
  if (!board_.IsValid(start) || !board_.IsValid(end))
    return false;
  if (std::abs(start.x - end.x) == 1 && std::abs(start.y - end.y) == 2)
    return true;
  if (std::abs(start.x - end.x) == 2 && std::abs(start.y - end.y) == 1)
    return true;
  return false;
}

std::vector<Coord> Knight::GetMoveSet(const Coord& start) const {
  std::vector<Coord> moveset;
  auto addMoveset = [&](const Coord& end) {
    if (!board_.IsValid(end))
      return;
    if (!IsMoveValid(start, end))
      return;
    moveset.push_back(end);
  };

  addMoveset(Coord(start.x + 1, start.y + 2));
  addMoveset(Coord(start.x + 1, start.y - 2));
  addMoveset(Coord(start.x - 1, start.y + 2));
  addMoveset(Coord(start.x - 1, start.y - 2));
  addMoveset(Coord(start.x + 2, start.y + 1));
  addMoveset(Coord(start.x + 2, start.y - 1));
  addMoveset(Coord(start.x - 2, start.y + 1));
  addMoveset(Coord(start.x - 2, start.y - 1));

  return moveset;
}
