#include "Knight.h"
#include <cmath>
#include <iostream>

int Knight::GetDistance(const Coord& start, const Coord& end) const {
  if (!board_.IsValid(start) || !board_.IsValid(end))
    throw std::invalid_argument("Grid positions are invalid");
  switch (board_[end]) {
  case Cell::Water: return 2;
  case Cell::Lava: return 5;
  default: return 1;
  }
}

bool Knight::IsMoveValid(const Coord& start, const Coord& end) const {
  if (!board_.IsValid(start) || !board_.IsValid(end))
    return false;
  const Coord diff = end - start;
  const int x_dist = std::abs(diff.x);
  const int y_dist = std::abs(diff.y);
  if (
    !(x_dist == 1 && y_dist == 2) &&
    !(x_dist == 2 && y_dist == 1)
    )
    return false;

  // Rock squares cannot be used
  if (board_[end] == Cell::Rock)
    return false;

  // Barrier quares cannot be used AND cannot lie in the path
  //std::vector<Coord> path = {};
  //if (y_dist > x_dist) {
  //  path.push_back(Coord(start.x, start.y + diff.y / 2));
  //  path.push_back(Coord(start.x, end.y));
  //}
  //else {
  //  path.push_back(Coord(start.x + diff.x / 2, start.y));
  //  path.push_back(Coord(end.x, start.y));
  //}
  //path.push_back(end);
  //for (auto& cell : path) {
  //  if (board_[cell] == Cell::Barrier)
  //    return false;
  //}
  return true;
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

  addMoveset(start + Coord(1, 2));
  addMoveset(start + Coord(1, -2));
  addMoveset(start + Coord(-1, 2));
  addMoveset(start + Coord(-1, -2));
  addMoveset(start + Coord(2, 1));
  addMoveset(start + Coord(2, -1));
  addMoveset(start + Coord(-2, 1));
  addMoveset(start + Coord(-2, -1));

  return moveset;
}
