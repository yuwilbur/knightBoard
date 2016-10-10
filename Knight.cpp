#include "Knight.h"
#include <cmath>

bool Knight::IsMoveValid(const Coord& start, const Coord& end, const Board& board) const {
  if (!board.IsValid(start) || !board.IsValid(end))
    return false;

  // Check if move is teleportation
  if (board[start] == Cell::Teleport && board[end] == Cell::Teleport)
    return true;

  // Check if move is a valid knight move
  const Coord diff = end - start;
  const int x_dist = std::abs(diff.x);
  const int y_dist = std::abs(diff.y);
  if (
    !(x_dist == 1 && y_dist == 2) &&
    !(x_dist == 2 && y_dist == 1)
    )
    return false;

  // Rock squares cannot be used
  if (board[end] == Cell::Rock)
    return false;

  // Barrier quares cannot be used AND cannot lie in the path
  // Because int 1 / 2 = 0. I can determine which axis of direction the piece is moving with diff / 2
  // Example: If piece is moving in (1,2) direction, (1,2)/2 = (0,1). Major axis will be y
  // Assume that the knight can use any cells to reach the destination as long as it's moving towards it
  // Valid Examples (K = start/end, k = path):
  // K k    K .    K .
  // . k    k k    k .
  // . K    . K    k K
  auto IsBarrier = [&](const Coord& coord) -> bool { return (board[coord] == Cell::Barrier); };
  if (IsBarrier(end)) return false;
  const Coord majorAxis = diff / 2;
  const Coord minorAxis = diff - majorAxis;
  if (
    (IsBarrier(start + majorAxis) || IsBarrier(start + majorAxis * 2)) &&
    (IsBarrier(start + majorAxis) || IsBarrier(start + majorAxis + minorAxis)) &&
    (IsBarrier(start + minorAxis) || IsBarrier(start + majorAxis + minorAxis))
    )
    return false;

  return true;
}

int Knight::GetDistance(const Coord& start, const Coord& end, const Board& board) const {
  if (!board.IsValid(start) || !board.IsValid(end))
    throw std::invalid_argument("Grid coordinates are invalid");
  const int distance = 1;
  switch (board[end]) {
  case Cell::Water: return distance + 1; // Water counts as two moves when landed on
  case Cell::Lava: return distance + 4; // Lava counts as five moves when landed on
  default: return distance;
  }
}

std::vector<Coord> Knight::GetMoveSet(const Coord& start, const Board& board) const {
  if (!board.IsValid(start))
    throw std::invalid_argument("Starting coordinate is invalid");

  std::vector<Coord> moveset;
  auto addMoveset = [&](const Coord& end) {
    if (!board.IsValid(end))
      return;
    if (!IsMoveValid(start, end, board))
      return;
    moveset.push_back((board[end] == Cell::Teleport) ? board.GetTeleportEndpoint(end) : end);
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
